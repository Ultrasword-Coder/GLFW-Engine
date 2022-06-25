#include "attribute.hpp"

Sora::Attribute Sora::create_attribute(int pointer, int size, int type, int normalized, int vertex_size, int offset_bytes)
{
    return {pointer, size, type, normalized, vertex_size, offset_bytes};
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
    // std::cout << pointer << " " << size << " " << type << " " << normalized << " " << vertex_size_bytes << std::endl;
    this->enable_attrib();
    glVertexAttribPointer(this->pointer, this->size, this->type, this->normalized, this->vertex_size_bytes,
                          // if 64bit make 8 bytes -- else make 4 bytes | 8 bytes = long long, 4 bytes = int
                          (_32BIT) ? (void *)(this->offset_bytes) : (void *)((long long)this->offset_bytes));
}
