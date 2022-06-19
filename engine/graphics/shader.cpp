#pragma once

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>
#include <cassert>
#include <string.h>
#include <fstream>

#include "../utils.hpp"
#include "shader.hpp"

Sora::Shader::Shader(const char *vert, const char *frag)
{
    // parse shader strings
}

Sora::Shader::~Shader()
{
    this->clean();
}

void Sora::Shader::clean()
{
    glDeleteProgram(this->program);
}

void Sora::Shader::bind()
{
    glUseProgram(this->program);
}

void Sora::Shader::unbind()
{
    glUseProgram(0);
}

void Sora::Shader::compile_shader(uint type, const char *shader)
{
    uint id = glCreateShader(type);
    glShaderSource(id, 1, &shader, nullptr);
    glCompileShader(id);

    // error handling for compilation
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        // get the length of error then allocate space then yeet
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        // output the info
        std::cout << "[SHADER-COMPILE][shader.cpp] Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!\n"
                  << message << std::endl;
        assert(!"[SHADER-COMPILE][shader.cpp] Failed to compile shader!");
    }
}

// uniform setters
void Sora::Shader::uploadBool(const char *name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->program, name), (int)value);
}

void Sora::Shader::uploadInt(const char *name, int value) const
{
    glUniform1i(glGetUniformLocation(this->program, name), value);
}

void Sora::Shader::uploadFloat(const char *name, float value) const
{
    glUniform1f(glGetUniformLocation(this->program, name), value);
}

Sora::Shader Sora::load_shader_from_file(const char *filepath)
{
    SoraIO::File file(filepath);
    // parse file
    std::string fragment, vertex;

    int section = -1;
    while (file.has_next_line())
    {
        if (file.next_line() == Sora::VERT_SECTION)
        {
            section = 0;
        }
        else if (file.next_line() == Sora::FRAG_SECTION)
        {
            section = 1;
        }
        else
        {
            if (section == 0)
            {
                vertex.append(file.next_line() + '\n');
            }
            else if (section == 1)
            {
                fragment.append(file.next_line() + '\n');
            }
        }
        std::cout << "Section: " << section << "\t|Line Size: " << file.next_line().size() << "\t|Line: " << file.next_line() << std::endl;
    }
    file.clean();

    // finished reading
    std::cout << "VertexCode:\n"
              << vertex << "\nFragmentCode:\n"
              << fragment << std::endl;

    Sora::Shader result(vertex.c_str(), fragment.c_str());

    return result;
}
