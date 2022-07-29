#pragma once
#include "transform.hpp"

SoraComponent::Transform::Transform(float x, float y, float z) : SoraComponent::Component()
{
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
}

SoraComponent::Transform::Transform(glm::vec3 pos) : SoraComponent::Transform(pos.x, pos.y, pos.z) {}

SoraComponent::Transform::Transform() : SoraComponent::Transform(0.0f, 0.0f, 0.0f) {}

SoraComponent::Transform::~Transform() {}

void SoraComponent::Transform::on_ready() {}

void SoraComponent::Transform::update() {}

float SoraComponent::Transform::get_x()
{
    return this->pos.x;
}

float SoraComponent::Transform::get_y()
{
    return this->pos.y;
}

float SoraComponent::Transform::get_z()
{
    return this->pos.z;
}

glm::vec3 *SoraComponent::Transform::get_pos()
{
    return &this->pos;
}

inline SoraComponent::Transform SoraComponent::Transform::operator+(SoraComponent::Transform other)
{
    return SoraComponent::Transform(glm::vec3(this->pos.x + other.pos.x, this->pos.y + other.pos.y, this->pos.z + other.pos.z));
}

inline SoraComponent::Transform SoraComponent::Transform::operator-(SoraComponent::Transform other)
{
    return SoraComponent::Transform(glm::vec3(this->pos.x - other.pos.x, this->pos.y - other.pos.y, this->pos.z - other.pos.z));
}

inline void SoraComponent::Transform::operator-=(SoraComponent::Transform other)
{
    this->pos.x -= other.pos.x;
    this->pos.y -= other.pos.y;
    this->pos.z -= other.pos.z;
}

inline void SoraComponent::Transform::operator+=(SoraComponent::Transform other)
{
    this->pos.x += other.pos.x;
    this->pos.y += other.pos.y;
    this->pos.z += other.pos.z;
}

inline void SoraComponent::Transform::operator=(SoraComponent::Transform other)
{
    this->pos.x = other.pos.x;
    this->pos.y = other.pos.y;
    this->pos.z = other.pos.z;
}

inline bool SoraComponent::Transform::operator==(SoraComponent::Transform other)
{
    return (pos.x == other.pos.x && pos.y == other.pos.y && pos.z == other.pos.z);
}
