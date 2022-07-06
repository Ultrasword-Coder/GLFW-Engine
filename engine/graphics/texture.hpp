#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

#include "../engine.hpp"
#include "../utils.hpp"

typedef unsigned int uint;

namespace Sora
{

    struct TextureData
    {
        int width, height, channels;
        unsigned char *data;
        const char *file;

        void create();
        void clean();
    };

    class Texture2D
    {
    private:
        uint id, glStoreType;
        TextureData data;

    public:
        Texture2D();
        Texture2D(int width, int height, int channels);
        Texture2D(const char *file);
        ~Texture2D();

        void reupload_data();

        void create();
        void clean();
        void bind();
        void unbind();

        int get_width();
        int get_height();
        uint get_id();

        uint get_glStoreType();
        TextureData *get_texture_data();
    };
};
