#pragma once

#include <cstring>

#include "../engine.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/shader.hpp"

namespace Sora::TexUploadHandler
{
    const int MAX_BUFFER_SIZE = 8;

    template <typename tex>
    struct TexUpload
    {
        /*
            TexUpload struct:
            - adds texture pointers to an array
            - when upload,  upload all textures
            - max is 8 textures
            - any more will raise an error

            There is no need to clean these textures because filehandler takes care of them.
        */
        tex *textures[MAX_BUFFER_SIZE];
        int texture_ids[MAX_BUFFER_SIZE];
        int tex_count = 0;

        TexUpload();
        ~TexUpload();

        void upload_textures(Sora::Shader *shader, const char *name);
        void bind_textures();
        void unbind_textures();
        void add_texture(tex *texture);
    };
}
