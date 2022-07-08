#pragma once

#include "../mesh/vao.hpp"
#include "../mesh/buffer_object.hpp"

namespace Sora::VAOHandler
{
    // vector of current arrays
    struct VertexDataContainer
    {
        Sora::VAO vao;
        Sora::BufferObject<float> vertices;
        Sora::BufferObject<int> indices;

        void create();
        void clean();
    };
}
