#pragma once
#include "buffer_object.hpp"

template <typename Data>
Sora::BufferObject<Data>::BufferObject() {}

template <typename Data>
Sora::BufferObject<Data>::BufferObject(int size, int gl_type, int draw_type) : size(size), type(gl_type), draw_type(draw_type)
{
    this->array.resize(size, 0);
    this->create();
}

template <typename Data>
Sora::BufferObject<Data>::BufferObject(int size, int gl_type) : size(size), type(gl_type), draw_type(Sora::DEFAULT_DRAW_TYPE)
{
    this->array.resize(size, 0);
    this->create();
}

template <typename Data>
Sora::BufferObject<Data>::~BufferObject()
{
    this->clean();
}

template <typename Data>
void Sora::BufferObject<Data>::clean()
{
    this->array.clear();
    glDeleteBuffers(1, &this->id);
}

template <typename Data>
void Sora::BufferObject<Data>::create()
{
    glGenBuffers(1, &this->id);
}

template <typename Data>
void Sora::BufferObject<Data>::upload_data()
{
    // copy data to arr to upload
    Data arr[this->array.size()];
    std::copy(this->array.begin(), this->array.end(), arr);
    // bind then upload
    bind();
    glBufferData(this->type, this->size * sizeof(Data), arr, this->draw_type);
}

template <typename Data>
void Sora::BufferObject<Data>::set_data(Data *data, int size)
{
    for (int i = 0; i < size && i < this->size; i++)
        this->array[i] = data[i];
}

template <typename Data>
std::vector<Data> *Sora::BufferObject<Data>::get_data()
{
    return &this->array;
}

template <typename Data>
void Sora::BufferObject<Data>::bind()
{
    glBindBuffer(this->type, this->id);
}

template <typename Data>
void Sora::BufferObject<Data>::unbind()
{
    glBindBuffer(this->type, 0);
}

template <typename Data>
uint Sora::BufferObject<Data>::get_id()
{
    return this->id;
}

template <typename Data>
int Sora::BufferObject<Data>::get_type()
{
    return this->type;
}

template <typename Data>
int Sora::BufferObject<Data>::get_size()
{
    return this->size;
}
template <typename Data>
int Sora::BufferObject<Data>::get_draw_type()
{
    return this->draw_type;
}