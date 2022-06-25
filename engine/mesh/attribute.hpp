#include <GL/glew.h>
#include <iostream>

#include "../engine.hpp"

namespace Sora
{

    struct Attribute
    {
        int pointer;
        int size;
        int type;
        int normalized;
        int vertex_size_bytes;
        int offset_bytes;

        void enable_attrib();
        void disable_attrib();
        void establish_attrib();
    };

    Attribute create_attribute(int pointer, int size, int type, int normalized, int vertex_size_bytes, int offset_bytes);

}
