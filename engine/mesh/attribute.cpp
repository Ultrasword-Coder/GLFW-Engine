#include "attribute.hpp"

Sora::Attribute Sora::create_attribute(int pointer, int size, int type, int normalized, int vertex_size)
{
    return {pointer, size, type, normalized, vertex_size};
}

void Sora::Attribute::enable_attrib()
{
    glEnableVertexAttribArray(this->pointer);
}

void Sora::Attribute::disable_attrib()
{
    glEnableVertexAttribArray(0);
}

void Sora::Attribute::establish_attrib()
{
    std::cout << pointer << " " << size << " " << type << " " << normalized << " " << vertex_size_bytes << std::endl;
    this->enable_attrib();
    glVertexAttribPointer(this->pointer, this->size, this->type, this->normalized, this->vertex_size_bytes, (void *)0);
}
