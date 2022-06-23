#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/engine.hpp"

#include "engine/utils.cpp"
#include "engine/window.cpp"

#include "engine/graphics/shader.cpp"

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

    // ----- setup ---- //
    // testing shaders
    Sora::Shader shader = Sora::load_shader_from_file("assets/shaders/default.glsl");
    shader.create();

    // vertices
    float vertices[] = {
        // bottom left, bototm right, top right, top left
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

    Sora::VAO m_vao;
    m_vao.create();
    m_vao.bind();

    // unsigned int vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    Sora::BufferObject<float> vert(28, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vert.create();
    vert.bind();
    vert.set_data(vertices, 28);
    vert.upload_data();

    m_vao.add_attribute(Sora::create_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7));
    m_vao.add_attribute(Sora::create_attribute(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7));

    m_vao.enable_attribs();

    // index stuff
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

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
    while (!glfwWindowShouldClose(Sora::w_instance->window))
    {
        // clear errors /  flush em out
        glCheckError();
        glClear(Sora::CLEAR_BITS);

        // update call

        // render call
        shader.bind();
        m_vao.bind();
        m_vao.enable_attribs();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);
        shader.unbind();

        glCheckError();

        // update window
        window.update();
    }

    m_vao.clean();
    vert.clean();
    index.clean();
    shader.unbind();
    shader.clean();

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
