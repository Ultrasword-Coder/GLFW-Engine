#pragma once
#include "input.hpp"

static void Sora::Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // if unknown key, dismiss
    if (key < 0)
        return;
    // else activate
    if (action == GLFW_PRESS)
    {
        Sora::Input::keyboard[key] = true;
        Sora::Input::keyboard_clicked.insert(key);
        }
    else if (action == GLFW_RELEASE)
    {
        Sora::Input::keyboard[key] = false;
        Sora::Input::keyboard_hold[key] = false;
    }
    else if (action == GLFW_REPEAT)
    {
        Sora::Input::keyboard_hold[key] = true;
    }
}

static bool Sora::Input::is_key_pressed(int keycode)
{
    return Sora::Input::keyboard[keycode];
}

static bool Sora::Input::is_key_hold(int keycode)
{
    return Sora::Input::keyboard_hold[keycode];
}

static bool Sora::Input::is_key_clicked(int keycode)
{
    return Sora::Input::keyboard_clicked.find(keycode) != Sora::Input::keyboard_clicked.end();
}

static void Sora::Input::mouse_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Sora::Input::mpos.x = xpos;
    Sora::Input::mpos.y = ypos;
}

static void Sora::Input::mouse_enter_callback(GLFWwindow *window, int entered)
{
}

static void Sora::Input::mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (Sora::Input::prev_pressed)
    {
        Sora::Input::mouse_dragging = true;
    }
    else
    {
        Sora::Input::mouse_dragging = false;
        Sora::Input::prev_pressed = true;
    }
    Sora::Input::mouse[button] = true;
    Sora::Input::mouse_clicked[button] = true;
}

static void Sora::Input::mouse_scroll_callback(GLFWwindow *window, double xoff, double yoff)
{
    Sora::Input::mscroll.x += xoff;
    Sora::Input::mscroll.y += yoff;
}

static bool Sora::Input::is_mouse_clicked(int keycode)
{
    return Sora::Input::mouse_clicked[keycode];
}

static bool Sora::Input::is_mouse_pressed(int keycode)
{
    return Sora::Input::mouse[keycode];
}

static bool Sora::Input::is_mouse_dragging()
{
    return Sora::Input::mouse_dragging;
}

static void Sora::Input::update()
{
    Sora::Input::keyboard_clicked.clear();
    for (int i = 0; i < GLFW_MOUSE_KEYS; i++)
        Sora::Input::mouse_clicked[i] = false;
}
