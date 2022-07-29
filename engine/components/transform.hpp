#pragma once
#include <GLM/glm.hpp>

#include "component.cpp"

namespace SoraComponent
{

    struct Transform : public SoraComponent::Component
    {
        glm::vec3 pos;

        Transform(float x, float y, float z);
        Transform(glm::vec3 pos);
        Transform();
        ~Transform();

        virtual void on_ready() override;
        virtual void update() override;

        float get_x();
        float get_y();
        float get_z();
        glm::vec3 *get_pos();

        inline bool operator==(SoraComponent::Transform other);
        inline void operator+=(SoraComponent::Transform other);
        inline void operator-=(SoraComponent::Transform other);
        inline SoraComponent::Transform operator-(SoraComponent::Transform other);
        inline SoraComponent::Transform operator+(SoraComponent::Transform other);
        inline void operator=(SoraComponent::Transform other);
    };

}
