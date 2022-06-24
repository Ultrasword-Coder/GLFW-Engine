#pragma once
#include "time.hpp"

static void Sora::Time::start()
{
    Sora::Time::start_time = Sora::Time::get_time();
    Sora::Time::end_time = Sora::Time::start_time;
}

static float Sora::Time::get_time()
{
    return (float)glfwGetTime();
}

static float Sora::Time::get_time_passed()
{
    return get_time() - Sora::Time::start_time;
}

static void Sora::Time::update()
{
    // update delta time
    Sora::Time::start_time = Sora::Time::get_time();
    Sora::Time::delta_time = Sora::Time::end_time - Sora::Time::start_time;
    Sora::Time::end_time = Sora::Time::start_time;
}
