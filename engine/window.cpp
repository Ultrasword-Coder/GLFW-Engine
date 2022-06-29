#pragma once

#include <iostream>
#include <cassert>

#include "window.hpp"

// static methods
void Sora::set_clear_bits(int bits)
{
    Sora::CLEAR_BITS = bits;
}

void Sora::set_clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

// window
Sora::Window::Window() : width(Sora::DEFAULT_WIDTH), height(Sora::DEFAULT_HEIGHT), title(Sora::DEFAULT_TITLE)
{
}

Sora::Window::Window(int width, int height, const char *title)
{
    this->width = width;
    this->height = height;
    this->title = title;
}

Sora::Window::~Window()
{
}

void Sora::Window::create()
{
    // create the window
    this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
    if (!window)
    {
        // failed to create window
        std::cout << "[window.cpp] Failed to create window!" << std::endl;
        assert(!"[window.cpp] Failed to create window!");
    }
    // set context current
    this->set_focus();
}

void Sora::Window::update()
{
    /*
        Update:
        - buffers
    */
    glfwSwapBuffers(this->window);
    glfwPollEvents();
    // VSYNC
    glfwSwapInterval(1);
}

void Sora::Window::clean()
{
    /*
        Clean the Window instance
    */
    glfwDestroyWindow(this->window);
}

void Sora::Window::set_focus()
{
    /*
        Set current window as focus
    */
    glfwMakeContextCurrent(this->window);
    Sora::w_instance = this;
}

int Sora::Window::get_width()
{
    return this->width;
}

int Sora::Window::get_height()
{
    return this->height;
}

void Sora::Window::window_size_callback(GLFWwindow *window, int width, int height)
{
    // std::cout << "window resized to\tw:" << width << "|h: " << height << std::endl;
    glViewport(0, 0, width, height);
}
