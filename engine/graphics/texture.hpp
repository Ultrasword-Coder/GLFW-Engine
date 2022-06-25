#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <STB/stb_image.h>

typedef unsigned int uint;

namespace Sora
{

    class Texture2D
    {
    private:
        uint id;
        int width, height, channels;
        const char *file;

    public:
        Texture2D(const char *file);
        ~Texture2D();

        void create();
        void clean();
        void bind();
        void unbind();
        int get_width();
        int get_height();
        uint get_id();
    };
}
