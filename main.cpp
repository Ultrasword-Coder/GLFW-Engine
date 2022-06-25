#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>

#include "engine/engine.hpp"

#include "engine/time.cpp"
#include "engine/utils.cpp"
#include "engine/window.cpp"
#include "engine/input.cpp"

#include "engine/graphics/shader.cpp"
#include "engine/graphics/uniform_map.cpp"
#include "engine/graphics/texture.cpp"

#include "engine/mesh/buffer_object.cpp"
#include "engine/mesh/vao.cpp"

typedef unsigned int uint;

int main()
{
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
    Sora::Shader shader = Sora::load_shader_from_file("assets/shaders/default.glsl");
    shader.create();
    shader.bind();

    Sora::ShaderUtils::UniformMap u_map;
    u_map.set_entry(shader.uniform_location("utime"), "utime");
    // u_map.set_entry(shader.uniform_location("utex"), "utex");
    // std::cout << u_map.get_entry("utime") << std::endl;

    // ---- create texture
    Sora::Texture2D tex("assets/images/tilemap.png");
    tex.create();

    // bind texture once for now
    glActiveTexture(GL_TEXTURE0);
    tex.bind();
    shader.uploadInt("utex", 0);
    tex.unbind();

    Sora::Texture2D tex2("assets/images/jirachi.jpg");
    tex2.create();

    glActiveTexture(GL_TEXTURE1);
    tex2.bind();
    shader.uploadInt("utex2", 1);
    tex2.unbind();

    // --- end texture

    // vertices
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f   // top left
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

    // ---- end setup --- //

    // game loop
    Sora::Time::start();
    while (!glfwWindowShouldClose(Sora::w_instance->window))
    {
        // clear errors /  flush em out
        glCheckError();
        glClear(Sora::CLEAR_BITS);

        // update call
        // if (Sora::Input::is_key_pressed(GLFW_KEY_A))
        //     std::cout << "A";

        // render call
        glActiveTexture(GL_TEXTURE0);
        tex.bind();
        glActiveTexture(GL_TEXTURE1);
        tex2.bind();
        shader.bind();
        shader.uploadValue(u_map.get_entry("utime"), Sora::Time::get_time());
        m_vao.bind();
        m_vao.enable_attribs();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        m_vao.disable_attribs();
        m_vao.unbind();
        shader.unbind();
        tex.unbind();
        tex2.unbind();

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
    shader.unbind();
    shader.clean();
    tex.clean();
    tex2.clean();

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
