#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Sora::Time
{
    // ------------ pre def -------------- //
    static void start();
    static float get_time();
    static float get_time_passed();
    static void update();

    // ------------ start -------------- //

    float start_time;
    float end_time;

    float wait_time = 0.0f;
    float delta_time = 0.0f;

    float frames_per_second = 60.0f;
    float frame_time = 1 / frames_per_second;

}
