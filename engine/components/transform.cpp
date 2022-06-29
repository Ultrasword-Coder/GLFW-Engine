#pragma once
#include "transform.hpp"

Sora::Transform::Transform(float x, float y, float z) : Sora::Component()
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}

Sora::Transform::Transform(glm::vec3 pos) : Sora::Transform(pos.x, pos.y, pos.z) {}

Sora::Transform::Transform() : Sora::Transform(0.0f, 0.0f, 0.0f) {}

Sora::Transform::~Transform() {}

void Sora::Transform::on_ready() {}

void Sora::Transform::update() {}

float Sora::Transform::get_x()
{
    return this->pos.x;
}

float Sora::Transform::get_y()
{
    return this->pos.y;
}

float Sora::Transform::get_z()
{
    return this->pos.z;
}

glm::vec3 *Sora::Transform::get_pos()
{
    return &this->pos;
}

inline Sora::Transform Sora::Transform::operator+(Sora::Transform other)
{
    return Sora::Transform(glm::vec3(this->pos.x + other.pos.x, this->pos.y + other.pos.y, this->pos.z + other.pos.z));
}

inline Sora::Transform Sora::Transform::operator-(Sora::Transform other)
{
    return Sora::Transform(glm::vec3(this->pos.x - other.pos.x, this->pos.y - other.pos.y, this->pos.z - other.pos.z));
}

inline void Sora::Transform::operator-=(Sora::Transform other)
{
    this->pos.x -= other.pos.x;
    this->pos.y -= other.pos.y;
    this->pos.z -= other.pos.z;
}

inline void Sora::Transform::operator+=(Sora::Transform other)
{
    this->pos.x += other.pos.x;
    this->pos.y += other.pos.y;
    this->pos.z += other.pos.z;
}

inline void Sora::Transform::operator=(Sora::Transform other)
{
    this->pos.x = other.pos.x;
    this->pos.y = other.pos.y;
    this->pos.z = other.pos.z;
}

inline bool Sora::Transform::operator==(Sora::Transform other)
{
    return (pos.x == other.pos.x && pos.y == other.pos.y && pos.z == other.pos.z);
}
