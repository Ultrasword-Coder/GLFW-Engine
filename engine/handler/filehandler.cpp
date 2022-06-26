#include "filehandler.hpp"

Sora::Shader *Sora::Filehandler::get_shader(const char *path)
{
    // check if already loaded
    if (Sora::Filehandler::shaders.find(path) != Sora::Filehandler::shaders.end())
        return &Sora::Filehandler::shaders[path];
    // else load
    Sora::Filehandler::shaders[path] = Sora::load_shader_from_file(path);
    Sora::Filehandler::shaders[path].create();
    return &Sora::Filehandler::shaders[path];
}

Sora::Texture2D *Sora::Filehandler::get_texture(const char *path)
{
    if (Sora::Filehandler::textures.find(path) != Sora::Filehandler::textures.end())
        return &Sora::Filehandler::textures[path];
    Sora::Filehandler::textures[path] = Sora::Texture2D(path);
    Sora::Filehandler::textures[path].create();
    return &Sora::Filehandler::textures[path];
}

void Sora::Filehandler::clean(int verbose)
{
    // clean the maps
    for (std::pair<const char *, Sora::Texture2D> element : Sora::Filehandler::textures)
    {
        // clean!
        element.second.clean();
        if (verbose > 1)
            std::cout << "[Sora][FileCleaning][filehandler.cpp] Cleaned up Texture2D from: " << element.first << std::endl;
    }
    for (std::pair<const char *, Sora::Shader> element : Sora::Filehandler::shaders)
    {
        // clean!
        element.second.clean();
        if (verbose > 1)
            std::cout << "[Sora][FileCleaning][filehandler.cpp] Cleaned up Shader from: " << element.first << std::endl;
    }
    // anything else added must be cleaned!
}
