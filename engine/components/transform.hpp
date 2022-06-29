#pragma once
#include <GLM/glm.hpp>

#include "component.cpp"

namespace Sora
{

    struct Transform : public Sora::Component
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

        inline bool operator==(Sora::Transform other);
        inline void operator+=(Sora::Transform other);
        inline void operator-=(Sora::Transform other);
        inline Sora::Transform operator-(Sora::Transform other);
        inline Sora::Transform operator+(Sora::Transform other);
        inline void operator=(Sora::Transform other);
    };

}
