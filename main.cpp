#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <glm/glm.hpp>

#include "engine/engine.hpp"

#include "engine/time.cpp"
#include "engine/utils.cpp"
#include "engine/window.cpp"
#include "engine/input.cpp"

#include "engine/handler/filehandler.cpp"

#include "engine/graphics/shader.cpp"
#include "engine/graphics/uniform_map.cpp"
#include "engine/graphics/texture.cpp"
#include "engine/graphics/framebuffer.cpp"

#include "engine/mesh/buffer_object.cpp"
#include "engine/mesh/vao.cpp"

#include "engine/components/transform.cpp"

#include "engine/objects/camera.cpp"

typedef unsigned int uint;

int main()
{
    // ----- just floating point stuff ------
    set_io_floating_precision(3);
    // --------------------------------------
    Sora::init_engine(Sora::VERY_VERBOSE);
    Sora::Window window;
    window.create();
    Sora::init_glew(Sora::VERY_VERBOSE);

    // window event callbacks
    glfwSetWindowSizeCallback(Sora::w_instance->window, Sora::Window::window_size_callback);
    glfwSetErrorCallback(glErrorCallback);
    glfwSetKeyCallback(Sora::w_instance->window, Sora::Input::key_callback);
    glfwSetCursorPosCallback(Sora::w_instance->window, Sora::Input::mouse_position_callback);
    glfwSetMouseButtonCallback(Sora::w_instance->window, Sora::Input::mouse_callback);
    glfwSetScrollCallback(Sora::w_instance->window, Sora::Input::mouse_scroll_callback);

    // ----- setup ---- //
    // testing shaders
    Sora::Shader *shader = Sora::Filehandler::get_shader("assets/shaders/default.glsl");
    shader->bind();

    Sora::ShaderUtils::UniformMap u_map;
    u_map.set_entry(shader->uniform_location("utime"), "utime");

    // ---- create texture
    Sora::Texture2D *tex = Sora::Filehandler::get_texture("assets/images/img1.png");

    // bind texture once for now
    glActiveTexture(GL_TEXTURE0);
    tex->bind();
    shader->uploadInt("utex", 0);
    tex->unbind();

    Sora::Texture2D *tex2 = Sora::Filehandler::get_texture("assets/images/img2.png");

    glActiveTexture(GL_TEXTURE1);
    tex2->bind();
    shader->uploadInt("utex2", 1);
    tex2->unbind();
    // --- end texture

    // ----- glm testing ---- //
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, -10.0f);

    SoraEngine::Camera3D camera(1280.0f, 720.0f);
    camera.set_position(pos);
    camera.set_target(0.0f, 0.0f, 0.0f);
    camera.update_projection();
    camera.calculate_vectors();

    shader->bind();
    shader->uploadMat4("view", camera.get_view());
    shader->uploadMat4("proj", camera.get_proj());
    // --- end glm ---- //

    // vertices
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, -0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f  // top left
    };
    // index stuff
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3};
    // create objects
    Sora::VAO m_vao;
    m_vao.create();
    m_vao.bind();
    Sora::BufferObject<float> vert(36, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vert.create();
    vert.bind();
    // data upload and set up
    vert.set_data(vertices, 36);
    vert.upload_data();
    int vertex_size_bytes = sizeof(float) * 9;
    m_vao.add_attribute(Sora::create_attribute(0, 3, GL_FLOAT, GL_FALSE, vertex_size_bytes, 0));
    m_vao.add_attribute(Sora::create_attribute(1, 4, GL_FLOAT, GL_FALSE, vertex_size_bytes, sizeof(float) * 3));
    m_vao.add_attribute(Sora::create_attribute(2, 2, GL_FLOAT, GL_FALSE, vertex_size_bytes, sizeof(float) * 7));
    Sora::BufferObject<uint> index(6, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    index.create();
    index.bind();
    index.set_data(indices, 6);
    index.upload_data();
    // unbind everything
    m_vao.disable_attribs();
    m_vao.unbind();
    vert.unbind();
    index.unbind();

    // floor vertices

    Sora::Shader *f_shader = Sora::Filehandler::get_shader("assets/shaders/floor.glsl");
    f_shader->bind();
    Sora::Texture2D *f_tex = Sora::Filehandler::get_texture("assets/images/floor.png");
    // big issue with glactive texture

    glActiveTexture(GL_TEXTURE0);
    f_tex->bind();
    f_shader->uploadInt("tex", 0);
    f_tex->unbind();
    f_shader->uploadMat4("proj", camera.get_proj());
    f_shader->unbind();

    float floor_vertices[] = {//  top right, bototm right, bottomleft, top left
                              // position            // texcoords
                              2.0f, -3.0f, 2.0f, 1.0f, 1.0f,
                              2.0f, -0.0f, -2.0f, 1.0f, -1.0f,
                              -2.0f, -0.0f, -2.0f, -1.0f, -1.0f,
                              -2.0f, -3.0f, 2.0f, 0.0f, 1.0f};
    Sora::VAO f_vao;
    f_vao.create();
    f_vao.bind();
    Sora::BufferObject<float> f_vert(20, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    f_vert.create();
    f_vert.bind();
    f_vert.set_data(floor_vertices, 20);
    f_vert.upload_data();
    f_vao.add_attribute(Sora::create_attribute(0, 3, GL_FLOAT, GL_FALSE, 20, 0));
    f_vao.add_attribute(Sora::create_attribute(1, 2, GL_FLOAT, GL_FALSE, 20, 12));
    Sora::BufferObject<uint> f_index(6, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    f_index.create();
    f_index.bind();
    f_index.set_data(indices, 6);
    f_index.upload_data();
    // unbind
    f_vao.disable_attribs();
    f_vao.unbind();
    f_vert.unbind();
    f_index.unbind();

    // ---- framebuffer --- //
    Sora::FrameBuffer framebuffer(1280, 720, 4);
    framebuffer.create();
    framebuffer.bind();
    glEnable(GL_DEPTH_TEST);
    framebuffer.unbind();

    Sora::Texture2D *frame_image = framebuffer.get_frame();

    // ---- end setup --- //

    // game loop
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    Sora::set_clear_bits(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sora::set_clear_color(0.6f, 0.0f, 0.2f, 1.0f);
    Sora::Time::start();
    while (!glfwWindowShouldClose(Sora::w_instance->window))
    {
        // clear errors /  flush em out
        glCheckError();
        glClearColor(0.6f, 0.0f, 0.2f, 1.0f);
        glClear(Sora::CLEAR_BITS);

        // update call
        if (Sora::Input::is_key_pressed(GLFW_KEY_W))
        {
            // move forward
            pos += camera.get_rdirection() * 5.0f * Sora::Time::delta_time;
            // pos.z -= 5.0f * Sora::Time::delta_time;
        }
        if (Sora::Input::is_key_pressed(GLFW_KEY_S))
        {
            pos += camera.get_rdirection() * -5.0f * Sora::Time::delta_time;
            // pos.z += 5.0f * Sora::Time::delta_time;
        }
        if (Sora::Input::is_key_pressed(GLFW_KEY_A))
        {
            pos += camera.get_left() * 5.0f * Sora::Time::delta_time;
            // pos.x -= 5.0f * Sora::Time::delta_time;
        }
        if (Sora::Input::is_key_pressed(GLFW_KEY_D))
        {
            pos += camera.get_left() * -5.0f * Sora::Time::delta_time;
            // pos.x += 5.0f * Sora::Time::delta_time;
        }
        camera.set_position(pos);
        camera.update();

        // render call
        // framebuffer render
        framebuffer.bind();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(Sora::CLEAR_BITS);
        // gigachad render
        glActiveTexture(GL_TEXTURE0);
        tex->bind();
        glActiveTexture(GL_TEXTURE1);
        tex2->bind();
        shader->bind();
        // upload variables
        shader->uploadMat4("view", camera.get_view());
        shader->uploadValue(u_map.get_entry("utime"), Sora::Time::get_time());
        // vertex array object
        m_vao.bind();
        m_vao.enable_attribs();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        m_vao.disable_attribs();
        m_vao.unbind();
        shader->unbind();
        tex->unbind();
        tex2->unbind();

        glCheckError();
        // end gigachad
        framebuffer.unbind();

        glActiveTexture(GL_TEXTURE0);
        tex->bind();
        glActiveTexture(GL_TEXTURE1);
        tex2->bind();
        shader->bind();
        // upload variables
        shader->uploadMat4("view", camera.get_view());
        shader->uploadValue(u_map.get_entry("utime"), Sora::Time::get_time());
        // vertex array object
        m_vao.bind();
        m_vao.enable_attribs();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        m_vao.disable_attribs();
        m_vao.unbind();
        shader->unbind();
        tex->unbind();
        tex2->unbind();

        glCheckError();

        // render ground
        glActiveTexture(GL_TEXTURE0);
        // empty.bind();
        // f_tex->bind();
        frame_image->bind();
        f_shader->bind();
        f_shader->uploadMat4("view", camera.get_view());
        f_vao.bind();
        f_vao.enable_attribs();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        f_vao.disable_attribs();
        f_vao.unbind();
        f_shader->unbind();
        // empty.unbind();
        // f_tex->unbind();
        frame_image->unbind();

        glCheckError();

        // update window
        window.update();
        Sora::Input::update();
        Sora::Time::update();
    }
    // std::cout << std::endl;

    m_vao.clean();
    vert.clean();
    index.clean();
    f_vao.clean();
    f_vert.clean();
    f_index.clean();
    framebuffer.clean();
    Sora::Filehandler::clean(Sora::VERY_VERBOSE);

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
