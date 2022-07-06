#pragma once

#include "texture.hpp"

// -------- texture data  holder -------- //

void Sora::TextureData::create()
{
    // only cache the data
    if (this->file)
    { // if a file is supplied, open file and load with that
        stbi_set_flip_vertically_on_load(true);
        this->data = stbi_load(this->file, &this->width, &this->height, &this->channels, 0);
        if (!this->data)
        {
            std::cout << "[Sora][TEXTURE-CREATION][" << __FILE__ << "][" << __LINE__ << "] Unable to load image from |" << this->file << "|" << std::endl;
            Sora::terminate_engine();
            return;
        }
    }
    else
    {
        this->data = (unsigned char *)malloc(sizeof(unsigned char) * this->width * this->height * this->channels);
        if (!this->data)
        {
            std::cout << "[Sora][TextureBufferFAIL][" << __FILE__ "][" << __LINE__ << "] Failed to allocate memory for texture!" << std::endl;
            Sora::terminate_engine();
        }
        // memset
        for (int i = 0; i < this->width * this->height * this->channels; i++)
            this->data[i] = 0;
    }
}

void Sora::TextureData::clean()
{
    // clean file data
    free(this->data);
}

// -------- texture 2d ----------- //

Sora::Texture2D::Texture2D() {}

Sora::Texture2D::Texture2D(int width, int height, int channels)
{
    this->data.width = width;
    this->data.height = height;
    this->data.channels = channels;
    this->data.file = 0;
}

Sora::Texture2D::Texture2D(const char *file)
{
    this->data.width = 0;
    this->data.height = 0;
    this->data.channels = 0;
    this->data.file = file;
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

    // if a file has been given -- load the file
    // if a file was not given, then generate an empty texture (width * height * sizeof(unsigned char) * channels)
    this->data.create();

    // either an image buffer has been created OR
    // image has been loaded
    // either way, a buffer has been created

    // load image stuffs
    this->reupload_data();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Sora::Texture2D::reupload_data()
{
    this->bind();
    if (this->data.channels == 1) // 1 layer
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R, this->data.width, this->data.height, 0, GL_R, GL_UNSIGNED_BYTE, this->data.data);
        this->glStoreType = GL_R;
    }
    else if (this->data.channels == 2) // 2 layers
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, this->data.width, this->data.height, 0, GL_RG, GL_UNSIGNED_BYTE, this->data.data);
        this->glStoreType = GL_RG;
    }
    else if (this->data.channels == 3) // jpg, jpeg, etc
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->data.width, this->data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data.data);
        glGenerateMipmap(GL_TEXTURE_2D);
        this->glStoreType = GL_RGB;
    }
    else if (this->data.channels == 4) // png
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->data.width, this->data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data.data);
        glGenerateMipmap(GL_TEXTURE_2D);
        this->glStoreType = GL_RGBA;
    }
}

void Sora::Texture2D::clean()
{
    glDeleteTextures(1, &this->id);
    this->data.clean();
}

void Sora::Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Sora::Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint Sora::Texture2D::get_id()
{
    return this->id;
}

uint Sora::Texture2D::get_glStoreType()
{
    return this->glStoreType;
}

int Sora::Texture2D::get_width()
{
    return this->data.width;
}

int Sora::Texture2D::get_height()
{
    return this->data.height;
}

Sora::TextureData *Sora::Texture2D::get_texture_data()
{
    return &this->data;
}
