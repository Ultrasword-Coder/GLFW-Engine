#pragma once
#include "vao.hpp"

Sora::VAO::VAO()
{
}

Sora::VAO::~VAO()
{
    this->clean();
}

void Sora::VAO::create()
{
    glGenVertexArrays(1, &this->id);
}

void Sora::VAO::clean()
{
    glDeleteVertexArrays(1, &this->id);
}

void Sora::VAO::add_attribute(Sora::Attribute attrib)
{
    this->attribs.push_back(attrib);
    attrib.establish_attrib();
}

void Sora::VAO::enable_attribs()
{
    for (Sora::Attribute attrib : this->attribs)
        attrib.enable_attrib();
}

void Sora::VAO::disable_attribs()
{
    for (Sora::Attribute attrib : this->attribs)
        attrib.disable_attrib();
}

void Sora::VAO::bind()
{
    glBindVertexArray(this->id);
}

void Sora::VAO::unbind()
{
    glBindVertexArray(0);
}
