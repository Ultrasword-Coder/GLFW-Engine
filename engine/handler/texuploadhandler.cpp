#pragma once

#include "texuploadhandler.hpp"

template <typename tex>
Sora::TexUploadHandler::TexUpload<tex>::TexUpload()
{
    memset(this->textures, 0, sizeof(this->textures));
    for (uint i = 0; i < Sora::TexUploadHandler::MAX_BUFFER_SIZE; i++)
        this->texture_ids[i] = i;
}

template <typename tex>
Sora::TexUploadHandler::TexUpload<tex>::~TexUpload() {}

template <typename tex>
void Sora::TexUploadHandler::TexUpload<tex>::upload_textures(Sora::Shader *shader, const char *uniform_name)
{
    shader->uploadIntArray(uniform_name, Sora::TexUploadHandler::MAX_BUFFER_SIZE, this->texture_ids);
}

template <typename tex>
void Sora::TexUploadHandler::TexUpload<tex>::bind_textures()
{
    for (int i = 0; i < this->tex_count; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        this->textures[i]->bind();
    }
}

template <typename tex>
void Sora::TexUploadHandler::TexUpload<tex>::unbind_textures()
{
    for (int i = 0; i < this->tex_count; i++)
    {
        this->textures[i]->unbind();
    }
}

template <typename tex>
void Sora::TexUploadHandler::TexUpload<tex>::add_texture(tex *texture)
{
    if (this->tex_count >= Sora::MAX_TEXTURES_AT_ONCE)
    {
        std::cout << "[Sora][TexUploadOverflow][" << __FILE__ << "] Added one too many textures to the TexUpload struct!" << std::endl;
        Sora::terminate_engine();
        return;
    }
    this->textures[this->tex_count] = texture;
    this->tex_count++;
}
