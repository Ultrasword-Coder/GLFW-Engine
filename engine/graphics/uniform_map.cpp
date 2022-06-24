#pragma once
#include "uniform_map.hpp"

Sora::ShaderUtils::UniformMap::UniformMap()
{
}

Sora::ShaderUtils::UniformMap::~UniformMap()
{
    uniforms.clear();
}

void Sora::ShaderUtils::UniformMap::set_entry(int uniform_position, std::string name)
{
    if (uniform_position < 0)
    {
        std::cout << "[UNIFORM-ERROR][uniform_map.cpp] Uniform of name |" << name << "| could not be found within shader script!" << std::endl;
        uniform_position = 0;
    }
    uniforms[name] = uniform_position;
}

int Sora::ShaderUtils::UniformMap::get_entry(std::string name)
{
    if (uniforms.at(name.c_str()))
        return uniforms[name.c_str()];
    return 0;
}
