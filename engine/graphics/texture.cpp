#pragma once

#include "texture.hpp"

Sora::Texture2D::Texture2D() {}

Sora::Texture2D::Texture2D(const char *file) : file(file)
{
}

Sora::Texture2D::~Texture2D() {}

void Sora::Texture2D::create()
{
    // gen id
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    // tex parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate texture
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image_data = stbi_load(this->file, &this->width, &this->height, &this->channels, 0);

    if (!image_data)
    {
        std::cout << "[Sora][TEXTURE-CREATION][texture.cpp] Unable to load image from |" << this->file << "|" << std::endl;
        Sora::terminate_engine();
        return;
    }
    // load image stuffs
    if (this->channels == 3) // jpg, jpeg, etc
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else if (this->channels == 4) // png
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(image_data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Sora::Texture2D::clean()
{
    glDeleteTextures(1, &this->id);
}

void Sora::Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Sora::Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Sora::Texture2D::get_width()
{
    return this->width;
}

int Sora::Texture2D::get_height()
{
    return this->height;
}

uint Sora::Texture2D::get_id()
{
    return this->id;
}

const char *Sora::Texture2D::get_file()
{
    return this->file;
}
