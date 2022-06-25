#pragma once
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>
#include <cassert>

#include "window.hpp"

#if _WIN32 || _WIN64
#if _WIN64
#define _64BIT 1
#else
#define _32BIT 1
#endif
#endif

// check GCC / G++
#if __GNUC__
#if __x86_64__ || __ppc64
#define _64BIT 1
#define _32BIT 0
#else
#define _32BIT 1
#define _64BIT 0
#endif
#endif

namespace Sora
{

    const int VERBOSE = 1, VERY_VERBOSE = 2;

    // init glfw + glew
    static void error_callback(int error, const char *description)
    {
        std::cout << "[Sora][OPENGL ERROR][engine.hpp] " << description << std::endl;
    }

    void terminate_engine()
    {
        glfwSetWindowShouldClose(Sora::w_instance->window, 1);
        std::cout << "[Sora][Terminate-Engine] Sora Engine is being terminated due to an issue that has arisen!" << std::endl;
    }

    void init_engine(int verbose)
    {
        /*
            Initiates GLFW library
            - shoule be first function called in program
        */
        // output glfw version
        if (verbose > 0)
        {
            std::cout << "[Sora][GLFWINIT][engine.hpp] GLFW Version: " << glfwGetVersionString() << std::endl;
        }
        // init glfw
        if (!glfwInit())
        {
            std::cout << "[Sora][GLFWINIT][engine.hpp] GLFW failed to initialize!" << std::endl;
            assert(!"[Sora][GLFWINIT][engine.hpp] GLFW failed to initialize!");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // set profile to core
        if (verbose > 1)
        {
            std::cout << "[Sora][GLFWINIT][engine.hpp] Setting GLFW Context Version to 3.3 core" << std::endl;
        }

        // if apple...
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        std::cout << "[Sora][APPLE][engine.hpp] Using APPLE machine! OPENGL FORWARD COMPAT has been set to true!" << std::endl;
#endif

        // set error callback
        glfwSetErrorCallback(error_callback);
    }

    void init_glew(int verbose)
    {
        /*
            Inititates GLEW library
            - should only be run after creating a Sora::window instance
        */
        if (glewInit() != GLEW_OK)
        {
            // end window instance
            if (Sora::w_instance->window)
                Sora::w_instance->clean();
            std::cout << "[Sora][GLEWINIT][engine.hpp] Failed to initialize `GLEW`" << std::endl;
            assert(!"[Sora][GLEWINIT][engine.hpp] GLEW Failed to initialize!");
        }
    }

    void clean_engine(int verbose)
    {
        std::cout << "[Sora][GLFWTERMINATE][engine.hpp] Terminating GLFW!" << std::endl;
        glfwTerminate();
    }
}