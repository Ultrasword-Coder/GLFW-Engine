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
    GLint MAX_TEXTURES_AT_ONCE;
    const int DEBUG = 1, NO_DEBUG = 0;

    // init glfw + glew
    static void error_callback(int error, const char *description)
    {
        std::cout << "[Sora][OPENGL ERROR][engine.hpp] " << description << std::endl;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"

    void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const *message, void const *user_param)
    {
        auto const src_str = [source]()
        {
            switch (source)
            {
            case GL_DEBUG_SOURCE_API:
                return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION:
                return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER:
                return "OTHER";
            }
        }();

        auto const type_str = [type]()
        {
            switch (type)
            {
            case GL_DEBUG_TYPE_ERROR:
                return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY:
                return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE:
                return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER:
                return "MARKER";
            case GL_DEBUG_TYPE_OTHER:
                return "OTHER";
            }
        }();

        auto const severity_str = [severity]()
        {
            switch (severity)
            {
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW:
                return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM:
                return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH:
                return "HIGH";
            }
        }();
        std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
    }
#pragma GCC diagnostic pop

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
            Initiates the openAL library
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

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set profile to core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        if (verbose > 1)
        {
            std::cout << "[Sora][GLFWINIT][engine.hpp] Setting GLFW Context Version to " << glfwGetVersionString() << std::endl;
        }

        // if apple...
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        std::cout << "[Sora][APPLE][engine.hpp] Using APPLE machine! OPENGL FORWARD COMPAT has been set to true!" << std::endl;
#endif
        // set error callback
        glfwSetErrorCallback(error_callback);

        // debug setup
        // ------- openal init ----- //

        // ------------------------- //
    }

    void init_glew(int verbose, bool debug)
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
        if (verbose > 1)
        {
            std::cout << "[Sora][GLFWINIT][engine.hpp] OpenGL Version is set to " << glGetString(GL_VERSION) << std::endl;
        }
        if (debug)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(message_callback, nullptr);
            std::cout << "[Sora][GLFWINIT][engine.hpp] OpenGL Debugging has been enabled." << std::endl;
        }
    }

    void collect_engine_data(int verbose)
    {
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &Sora::MAX_TEXTURES_AT_ONCE);
        if (verbose > 1)
            std::cout << "[Sora][HWData][FragmentShaderTextures] This device can access `" << Sora::MAX_TEXTURES_AT_ONCE << "` textures in the fragment shader!" << std::endl;
    }

    void clean_engine(int verbose)
    {
        std::cout << "[Sora][GLFWTERMINATE][engine.hpp] Terminating GLFW!" << std::endl;
        glfwTerminate();
    }
}