#pragma once

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "texture.hpp"

typedef unsigned int uint;

namespace Sora
{

    class FrameBuffer
    {
    private:
        uint frame_buffer_object, render_buffer_object;
        Sora::Texture2D frame;

    public:
        FrameBuffer(int width, int height, int channels);
        ~FrameBuffer();

        void create();
        void clean();
        void bind();
        void unbind();

        uint get_id();
        uint get_render_id();

        Sora::Texture2D *get_frame();
    };

}