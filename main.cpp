#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/engine.hpp"

#include "engine/utils.cpp"
#include "engine/window.cpp"

#include "engine/graphics/shader.cpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    Sora::init_engine(Sora::VERY_VERBOSE);
    Sora::Window window;
    window.create();
    Sora::init_glew(Sora::VERY_VERBOSE);

    // ----- setup ---- //
    // testing shaders
    Sora::Shader shader = Sora::load_shader_from_file("assets/shaders/default.glsl");
    shader.create();

    // ---- end setup --- //

    // game loop
    while (!glfwWindowShouldClose(Sora::w_instance->window))
    {
        // clear errors /  flush em out
        glClearError();
        glClear(Sora::CLEAR_BITS);

        // update call

        // render call
        shader.bind();

        shader.unbind();

        // update window
        window.update();
    }

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
