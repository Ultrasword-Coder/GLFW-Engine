#pragma once

#include "vaohandler.hpp"

template <typename T, typename I>
Sora::VAOHandler<T, I> Sora::create_vao_handler(Sora::VAO vao, Sora::BufferObject<T> vertices, Sora::BufferObject<I> indices)
{
    Sora::VAOHandler<T, I> result;
    result.vao = vao;
    result.vertices = vertices;
    result.indices = indices;
    return result;
}

template <typename T, typename I>
Sora::VAOHandler<T, I>::VAOHandler() {}

template <typename T, typename I>
Sora::VAOHandler<T, I>::~VAOHandler() {}

template <typename T, typename I>
void Sora::VAOHandler<T, I>::create(T *vert_data, int vert_size, I *ind_data, int ind_size)
{
    // create the VAOhandler objects!
    // create vao
    vao.create();
    vao.bind();
    vertices.create();
    vertices.bind();
    vertices.set_data(vert_data, vert_size);
    vertices.upload_data();
    // create indices
    indices.create();
    indices.bind();
    indices.set_data(ind_data, ind_size);
    indices.upload_data();
    // unbind all data
}

template <typename T, typename I>
void Sora::VAOHandler<T, I>::clean()
{
    vao.clean();
    vertices.clean();
    indices.clean();
}

template <typename T, typename I>
Sora::VAO *Sora::VAOHandler<T, I>::get_vao()
{
    return &this->vao;
}

template <typename T, typename I>
Sora::BufferObject<T> *Sora::VAOHandler<T, I>::get_vertices()
{
    return &this->vertices;
}

template <typename T, typename I>
Sora::BufferObject<I> *Sora::VAOHandler<T, I>::get_indices()
{
    return &this->indices;
}

template <typename T, typename I>
void Sora::VAOHandler<T, I>::bind()
{
    vao.bind();
    vao.enable_attribs();
    // vertices.bind();
    // indices.bind();
}

template <typename T, typename I>
void Sora::VAOHandler<T, I>::unbind()
{
    vao.disable_attribs();
    vao.unbind();
    // vertices.unbind();
    // indices.unbind();
}
