#pragma once
#include <GLFW/glfw3.h>

#include <unordered_set>

namespace Sora::Input
{
    // keyboard
    const unsigned int GLFW_KEY_COUNT = GLFW_KEY_LAST;

    static bool keyboard[GLFW_KEY_COUNT];
    static bool keyboard_hold[GLFW_KEY_COUNT];
    static std::unordered_set<int> keyboard_clicked;

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static bool is_key_pressed(int keycode);
    static bool is_key_hold(int keycode);
    static bool is_key_clicked(int keycode);

    // mouse
    struct MousePos
    {
        double x, y;
    };

    const unsigned int GLFW_MOUSE_KEYS = GLFW_MOUSE_BUTTON_LAST;

    static bool mouse[GLFW_MOUSE_KEYS];
    static bool mouse_clicked[GLFW_MOUSE_KEYS];
    static bool prev_pressed = false;
    static bool mouse_dragging = false;

    static MousePos mpos;
    struct MousePos mscroll;

    static void mouse_position_callback(GLFWwindow *window, double xpos, double ypos);
    static void mouse_enter_callback(GLFWwindow *window, int entered);
    static void mouse_callback(GLFWwindow *window, int button, int action, int mods);
    static void mouse_scroll_callback(GLFWwindow *window, double xoff, double yoff);

    static bool is_mouse_clicked(int keycode);
    static bool is_mouse_pressed(int keycode);
    static bool is_mouse_dragging();

    // update
    static void update();

    static void clean(int verbose);

}
