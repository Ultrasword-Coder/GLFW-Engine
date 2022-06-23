#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/engine.hpp"

#include "engine/utils.cpp"
#include "engine/window.cpp"

#include "engine/graphics/shader.cpp"

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

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void *)0);

    // index stuff
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // std::cout << vao << " " << vbo << " " << ibo << std::endl;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);
        shader.unbind();

        glCheckError();

        // update window
        window.update();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &buffer);
    glDeleteBuffers(1, &ibo);
    shader.unbind();
    shader.clean();

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
