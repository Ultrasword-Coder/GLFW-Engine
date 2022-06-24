#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/engine.hpp"

#include "engine/time.cpp"
#include "engine/utils.cpp"
#include "engine/window.cpp"
#include "engine/input.cpp"

#include "engine/graphics/shader.cpp"
#include "engine/graphics/uniform_map.cpp"

#include "engine/mesh/buffer_object.cpp"
#include "engine/mesh/vao.cpp"

typedef unsigned int uint;

int main()
{
    std::cout << "Hello World" << std::endl;

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
    shader.uploadFloat("utime", Sora::Time::get_time_passed());

    Sora::ShaderUtils::UniformMap u_map;
    u_map.set_entry(shader.uniform_location("utime"), "utime");
    // std::cout << u_map.get_entry("utime") << std::endl;

    // vertices
    float vertices[] = {
        // bottom left, bototm right, top right, top left
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

    // index stuff
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    Sora::VAO m_vao;
    m_vao.create();
    m_vao.bind();

    Sora::BufferObject<float> vert(28, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vert.create();
    vert.bind();
    vert.set_data(vertices, 28);
    vert.upload_data();

    m_vao.add_attribute(Sora::create_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7));
    m_vao.add_attribute(Sora::create_attribute(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7));

    Sora::BufferObject<uint> index(6, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    index.create();
    index.bind();
    index.set_data(indices, 6);
    index.upload_data();

    // std::cout << vao << " " << vbo << " " << ibo << std::endl;
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
        if (Sora::Input::is_key_pressed(GLFW_KEY_A))
            std::cout << "AAAAAAAAAAAAAAAAAAAAAAA";

        // render call
        shader.bind();
        shader.uploadValue(u_map.get_entry("utime"), Sora::Time::get_time());
        m_vao.bind();
        m_vao.enable_attribs();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);
        shader.unbind();

        glCheckError();

        // update window
        window.update();
        Sora::Input::update();
        Sora::Time::update();
    }
    std::cout << std::endl;

    m_vao.clean();
    vert.clean();
    index.clean();
    shader.unbind();
    shader.clean();

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
