#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <glm/glm.hpp>

#include "engine/engine.hpp"

#include "engine/time.cpp"
#include "engine/utils.cpp"
#include "engine/window.cpp"
#include "engine/input.cpp"

#include "engine/graphics/shader.cpp"
#include "engine/graphics/uniform_map.cpp"
#include "engine/graphics/texture.cpp"
#include "engine/graphics/framebuffer.cpp"

#include "engine/mesh/buffer_object.cpp"
#include "engine/mesh/vao.cpp"

#include "engine/handler/filehandler.cpp"
#include "engine/handler/texuploadhandler.cpp"
#include "engine/handler/vaohandler.cpp"

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
    Sora::collect_engine_data(Sora::VERY_VERBOSE);

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
    Sora::Texture2D *tex2 = Sora::Filehandler::get_texture("assets/images/img2.png");

    /*
        NEXT TIME --
        MOVE TEXTURE UPLOADING INTO THE ALREADY MADE STRUCT
        the Sora::TexUploadHandler::TexUpload object!!!
    */

    Sora::TexUploadHandler::TexUpload<Sora::Texture2D> tex_handler;

    tex_handler.add_texture(tex);
    tex_handler.add_texture(tex2);

    tex_handler.bind_textures();
    tex_handler.upload_textures(shader, "utex");
    tex_handler.unbind_textures();

    // // bind texture once for now
    // glActiveTexture(GL_TEXTURE0);
    // tex->bind();
    // shader->uploadInt("utex", 0);
    // tex->unbind();

    // glActiveTexture(GL_TEXTURE1);
    // tex2->bind();
    // shader->uploadInt("utex2", 1);
    // tex2->unbind();

    // --------- floor shaders ---- //
    // floor vertices

    Sora::Shader *f_shader = Sora::Filehandler::get_shader("assets/shaders/floor.glsl");
    f_shader->bind();
    Sora::Texture2D *f_tex = Sora::Filehandler::get_texture("assets/images/floor.png");

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

    f_shader->bind();
    f_shader->uploadMat4("view", camera.get_view());
    f_shader->uploadMat4("proj", camera.get_proj());

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
    int vertex_size_bytes = sizeof(float) * 9;

    Sora::VAOHandler main_vao = Sora::create_vao_handler(Sora::VAO(), Sora::BufferObject<float>(36, GL_ARRAY_BUFFER, GL_STATIC_DRAW), Sora::BufferObject<uint>(6, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW));
    main_vao.create(vertices, 36, indices, 6);
    main_vao.get_vao()->add_attribute(Sora::create_attribute(0, 3, GL_FLOAT, GL_FALSE, vertex_size_bytes, 0));
    main_vao.get_vao()->add_attribute(Sora::create_attribute(1, 4, GL_FLOAT, GL_FALSE, vertex_size_bytes, sizeof(float) * 3));
    main_vao.get_vao()->add_attribute(Sora::create_attribute(2, 2, GL_FLOAT, GL_FALSE, vertex_size_bytes, sizeof(float) * 7));
    main_vao.unbind();

    // ------------ floor vertices ------------ //
    // big issue with glactive texture

    glActiveTexture(GL_TEXTURE0);
    f_tex->bind();
    f_shader->uploadInt("tex", 0);
    f_tex->unbind();
    f_shader->uploadMat4("proj", camera.get_proj());
    f_shader->unbind();

    float floor_vertices[] = {//  top right, bototm right, bottomleft, top left
                              // position            // texcoords
                              2.0f, -2.0f, 2.0f, 1.0f, 1.0f,
                              2.0f, -2.0f, -2.0f, 1.0f, 0.0f,
                              -2.0f, -2.0f, -2.0f, 0.0f, 0.0f,
                              -2.0f, -2.0f, 2.0f, 0.0f, 1.0f};
    Sora::VAOHandler<float, uint> floor_vao = Sora::create_vao_handler<float, uint>(Sora::VAO(), Sora::BufferObject<float>(20, GL_ARRAY_BUFFER, GL_STATIC_DRAW), Sora::BufferObject<uint>(6, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW));
    floor_vao.create(floor_vertices, 20, indices, 6);
    floor_vao.get_vao()->add_attribute(Sora::create_attribute(0, 3, GL_FLOAT, GL_FALSE, 20, 0));
    floor_vao.get_vao()->add_attribute(Sora::create_attribute(1, 2, GL_FLOAT, GL_FALSE, 20, 12));
    floor_vao.unbind();

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
        Sora::set_clear_color(0.6f, 0.0f, 0.2f, 1.0f);
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
        if (Sora::Input::is_key_pressed(GLFW_KEY_LEFT_SHIFT))
        {
            pos += camera.get_up() * 5.0f * Sora::Time::delta_time;
        }
        if (Sora::Input::is_key_pressed(GLFW_KEY_SPACE))
        {
            pos += camera.get_up() * -5.0f * Sora::Time::delta_time;
        }

        camera.set_position(pos);
        camera.update();

        // ------------- render call ------------- //

        // gigachad render
        tex_handler.bind_textures();
        shader->bind();
        shader->uploadMat4("view", camera.get_view());
        shader->uploadValue(u_map.get_entry("utime"), Sora::Time::get_time());
        main_vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        main_vao.unbind();
        shader->unbind();
        tex_handler.unbind_textures();
        glCheckError();

        // render ground
        glActiveTexture(GL_TEXTURE0);
        f_tex->bind();
        f_shader->bind();
        f_shader->uploadMat4("view", camera.get_view());
        floor_vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        floor_vao.unbind();
        f_shader->unbind();
        f_tex->unbind();
        glCheckError();

        // update window
        window.update();
        Sora::Input::update();
        Sora::Time::update();
    }

    main_vao.clean();
    floor_vao.clean();
    Sora::Filehandler::clean(Sora::VERY_VERBOSE);

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
