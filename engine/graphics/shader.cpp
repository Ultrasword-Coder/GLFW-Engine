#pragma once

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <iostream>
#include <cassert>
#include <string.h>
#include <fstream>
#include <sstream>

#include "../utils.hpp"
#include "shader.hpp"

Sora::Shader::Shader() {}

Sora::Shader::Shader(const char *file)
{
    // parse shader strings
    this->filepath = file;
}

Sora::Shader::~Shader() {}

void Sora::Shader::set_shader_code(std::string vert_code, std::string frag_code)
{
    this->vert_shader = vert_code;
    this->frag_shader = frag_code;
}

void Sora::Shader::create()
{
    if (this->created)
        return;
    uint vs, fs;

    vs = compile_shader(GL_VERTEX_SHADER, vert_shader.c_str());
    fs = compile_shader(GL_FRAGMENT_SHADER, frag_shader.c_str());
    program = glCreateProgram();

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        int length;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(program, length, &length, message);

        // output error
        std::cout << "[ValidateShaderProgram][shader.cpp] Failed to validate Shader program!\nShaderSource: :" << filepath << std::endl;
        assert(!"[ValidateShaderProgram][shader.cpp] Failed to validate shader program!");
    }

    // free memory
    glDeleteShader(vs);
    glDeleteShader(fs);
    this->created = true;
}

void Sora::Shader::clean()
{
    glDeleteProgram(this->program);
    this->unbind();
}

void Sora::Shader::bind()
{
    glUseProgram(this->program);
}

void Sora::Shader::unbind()
{
    glUseProgram(0);
}

const char *Sora::Shader::get_file()
{
    return this->filepath;
}

uint Sora::Shader::compile_shader(uint type, const char *shader)
{
    uint id = glCreateShader(type);
    glShaderSource(id, 1, &shader, NULL);
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
        assert(false);
    }
    return id;
}

// uniform setters
int Sora::Shader::uniform_location(const char *name) const
{
    glUseProgram(this->program);
    return glGetUniformLocation(this->program, name);
}

void Sora::Shader::uploadBool(const char *name, bool value) const
{
    glUniform1i(this->uniform_location(name), (int)value);
}

void Sora::Shader::uploadInt(const char *name, int value) const
{
    glUniform1i(this->uniform_location(name), value);
}

void Sora::Shader::uploadFloat(const char *name, float value) const
{
    glUniform1f(this->uniform_location(name), value);
}

void Sora::Shader::uploadTexture2D(const char *name, Sora::Texture2D *tex) const
{
    this->uploadInt(name, tex->get_id());
}

template <typename T>
void Sora::Shader::uploadValue(int pos, T value) const
{
    if (typeid(value) == FLOAT_ID)
        glUniform1f(pos, value);
    else if (typeid(value) == UINT_ID || typeid(value) == INT_ID)
        glUniform1i(pos, value);
    else
        std::cout << "[UNK-TYPE][shader.cpp] unknown type as of right now" << std::endl;
}

// matrix uniform upload
void Sora::Shader::uploadVec2(const char *name, glm::vec2 vec)
{
    glUniform2f(this->uniform_location(name), vec.x, vec.y);
}

void Sora::Shader::uploadVec3(const char *name, glm::vec3 vec)
{
    glUniform3f(this->uniform_location(name), vec.x, vec.y, vec.z);
}

void Sora::Shader::uploadVec4(const char *name, glm::vec4 vec)
{
    glUniform4f(this->uniform_location(name), vec.x, vec.y, vec.z, vec.w);
}

void Sora::Shader::uploadMat2(const char *name, glm::mat2 mat)
{
    glUniformMatrix2fv(this->uniform_location(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Sora::Shader::uploadMat3(const char *name, glm::mat3 mat)
{
    glUniformMatrix3fv(this->uniform_location(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Sora::Shader::uploadMat4(const char *name, glm::mat4 mat)
{
    glUniformMatrix4fv(this->uniform_location(name), 1, GL_FALSE, glm::value_ptr(mat));
}

// load shader from file

Sora::Shader Sora::load_shader_from_file(const char *filepath)
{
    SoraIO::File file(filepath);
    // parse file
    std::stringstream vertex, fragment;

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
                vertex << file.next_line() << '\n';
            }
            else if (section == 1)
            {
                fragment << file.next_line() << '\n';
            }
            // std::cout << "Section: " << section << "\t|Line Size: " << file.next_line().size() << "\t|Line: `" << file.next_line() << "`" << std::endl;
        }
    }
    file.clean();

    // finished reading
    // std::cout << "VertexCode:\n"
    //           << vertex.str() << "\nFragmentCode:\n"
    //           << fragment.str() << std::endl;
    Sora::Shader result(filepath);
    result.set_shader_code(vertex.str(), fragment.str());
    return result;
}
