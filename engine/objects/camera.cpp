#pragma once

#include "camera.hpp"

SoraEngine::Camera::Camera(float width, float height, float near, float far) : width(width), height(height), near(near), far(far) {}

SoraEngine::Camera::~Camera() {}

void SoraEngine::Camera::create() {}

void SoraEngine::Camera::update() {}

void SoraEngine::Camera::update_projection() {}

glm::vec3 SoraEngine::Camera::get_position()
{
    return this->position;
}

glm::vec3 SoraEngine::Camera::get_rdirection()
{
    return this->rdirection;
}

glm::vec3 SoraEngine::Camera::get_target()
{
    return this->target;
}

glm::vec3 SoraEngine::Camera::get_up()
{
    return this->camera_up;
}

glm::vec3 SoraEngine::Camera::get_right()
{
    return this->camera_right;
}

glm::mat4 SoraEngine::Camera::get_view()
{
    return this->view;
}

glm::mat4 SoraEngine::Camera::get_proj()
{
    return this->proj;
}

void SoraEngine::Camera::calculate_vectors() {}

void SoraEngine::Camera::set_position(glm::vec3 pos)
{
    this->position = pos;
}

void SoraEngine::Camera::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void SoraEngine::Camera::set_target(glm::vec3 pos)
{
    this->target = pos;
}

void SoraEngine::Camera::set_target(float x, float y, float z)
{
    this->target = glm::vec3(x, y, z);
}

// ------- camera 2D -------

SoraEngine::Camera2D::Camera2D(float width, float height) : SoraEngine::Camera(width, height, 0.1f, 100.0f) {}

SoraEngine::Camera2D::Camera2D(float width, float height, float near, float far) : SoraEngine::Camera(width, height, near, far) {}

SoraEngine::Camera2D::~Camera2D() {}

void SoraEngine::Camera2D::create()
{
    this->update_projection();
}

void SoraEngine::Camera2D::update()
{
    this->calculate_vectors();
    this->view = glm::lookAt(this->position, this->target, this->camera_up);
}

void SoraEngine::Camera2D::calculate_vectors()
{
    // rdirection
    this->rdirection = glm::normalize(this->position - this->target);
    // camera right
    this->camera_right = glm::normalize(glm::cross(SoraEngine::UP, this->rdirection));
    // camera up
    this->camera_up = glm::cross(this->rdirection, this->camera_right);
}

void SoraEngine::Camera2D::update_projection()
{
    this->proj = glm::ortho(0.0f, this->width, 0.0f, this->height, 0.0f, 100.0f);
}

// --------- camera 3d -----------

SoraEngine::Camera3D::Camera3D(float width, float height) : a_ratio(width / height), fov(45.0f), SoraEngine::Camera(width, height, 0.1f, 100.0f) {}

SoraEngine::Camera3D::Camera3D(float width, float height, float near, float far) : a_ratio(width / height), fov(45.0f), SoraEngine::Camera(width, height, near, far) {}

SoraEngine::Camera3D::Camera3D(float width, float height, float near, float far, float fov) : fov(fov), a_ratio(width / height), SoraEngine::Camera(width, height, near, far) {}

SoraEngine::Camera3D::~Camera3D() {}

void SoraEngine::Camera3D::create() {}

void SoraEngine::Camera3D::update()
{
    this->calculate_vectors();
    this->view = glm::lookAt(this->position, this->target, this->camera_up);
}

void SoraEngine::Camera3D::calculate_vectors()
{
    // rdirection
    this->rdirection = glm::normalize(this->position - this->target);
    // camera right
    this->camera_right = glm::normalize(glm::cross(SoraEngine::UP, this->rdirection));
    // camera up
    this->camera_up = glm::cross(this->rdirection, this->camera_right);
}

void SoraEngine::Camera3D::update_projection()
{
    this->proj = glm::perspective(glm::radians(this->fov), this->a_ratio, this->near, this->far);
}
