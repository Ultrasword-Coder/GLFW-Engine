#pragma once

#include "../mesh/vao.hpp"
#include "../mesh/buffer_object.hpp"

namespace Sora
{
    // vector of current arrays
    template <typename T, typename I>
    struct VAOHandler
    {
        Sora::VAO vao;
        Sora::BufferObject<T> vertices;
        Sora::BufferObject<I> indices;

        VAOHandler();
        ~VAOHandler();

        void create(T *vert_data, int vert_size, I *ind_data, int ind_size);
        void clean();

        Sora::VAO *get_vao();
        Sora::BufferObject<T> *get_vertices();
        Sora::BufferObject<I> *get_indices();

        void bind();
        void unbind();
    };

    template <typename T, typename I>
    Sora::VAOHandler<T, I> create_vao_handler(Sora::VAO vao, Sora::BufferObject<T>, Sora::BufferObject<I>);

}
