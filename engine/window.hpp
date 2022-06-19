#pragma once
#include <GLFW/glfw3.h>

namespace Sora
{
    const int DEFAULT_WIDTH = 1280, DEFAULT_HEIGHT = 720;
    const char *DEFAULT_TITLE = "Sora";

    int CLEAR_BITS = GL_COLOR_BUFFER_BIT;

    // static methods
    static void set_clear_bits(int bits);

    // window class
    class Window
    {
    private:
        int width, height;
        const char *title;

    public:
        GLFWwindow *window;

        // constructors
        Window();
        Window(int width, int height, const char *title);
        ~Window();

        void create();
        void update();
        void clean();
        void set_focus();

        // -------- static --------- //
        static void window_size_callback(GLFWwindow *window, int width, int height);
    };

    // instance
    Window *w_instance;

}