#pragma once
#include <GL/glew.h>

#include <vector>

#include "attribute.cpp"
#include "buffer_object.cpp"

namespace Sora
{

    class VAO
    {
    private:
        std::vector<Sora::Attribute> attribs;
        uint id;

    public:
        VAO();
        ~VAO();

        void create();
        void clean();
        void add_attribute(Sora::Attribute attrib);
        void enable_attribs();
        void disable_attribs();
        void bind();
        void unbind();
    };

}