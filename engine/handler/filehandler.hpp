#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"

namespace Sora::Filehandler
{

    // texture map and shader map
    std::unordered_map<const char *, Sora::Texture2D> textures;
    std::unordered_map<const char *, Sora::Shader> shaders;

    Sora::Shader *get_shader(const char *);
    Sora::Texture2D *get_texture(const char *);

    void clean(int verbose);

}
