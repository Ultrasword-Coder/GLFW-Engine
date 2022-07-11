#pragma once
#include <GL/glew.h>

#include <vector>
#include <iostream>
#include <algorithm>

typedef unsigned int uint;

namespace Sora
{
    const int DEFAULT_DRAW_TYPE = GL_STATIC_DRAW;

    template <typename Data>
    class BufferObject
    {
    private:
        uint id;
        int type;
        int size;
        int draw_type;
        std::vector<Data> array;

    public:
        BufferObject();
        BufferObject(int size, int type, int draw_type);
        BufferObject(int size, int type);
        ~BufferObject();

        void create();
        void clean();
        void upload_data();
        void set_data(Data *data, int size);
        std::vector<Data> *get_data();

        void bind();
        void unbind();
    };

}
