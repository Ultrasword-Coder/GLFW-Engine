/*
    Structure meant to keep track of uniform variables and their locations in shaders
*/
#pragma once
#include <GL/glew.h>

#include <unordered_map>
#include <string>

#include "../graphics/shader.cpp"

namespace Sora::ShaderUtils
{
    class UniformMap
    {
    private:
        std::unordered_map<std::string, int> uniforms;

    public:
        UniformMap();
        ~UniformMap();

        void set_entry(int uniform_position, std::string name);
        int get_entry(std::string name);
    };

}
