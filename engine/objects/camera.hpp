#pragma once

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

namespace SoraEngine
{
    const glm::vec3 UP(0.0f, 1.0f, 0.0f);

    class Camera
    {
    protected:
        float width, height, near, far;
        glm::vec3 position, target, rdirection;
        glm::vec3 camera_left, camera_up;
        glm::mat4 view, proj;

    public:
        Camera(float width, float height, float near, float far);
        Camera(glm::vec3 pos);
        ~Camera();

        virtual void create();
        virtual void update();
        virtual void update_projection();

        glm::vec3 get_position();
        glm::vec3 get_rdirection();
        glm::vec3 get_target();
        glm::vec3 get_up();
        glm::vec3 get_left();
        glm::mat4 get_view();
        glm::mat4 get_proj();

        virtual void calculate_vectors();

        void set_position(glm::vec3 pos);
        void set_position(float x, float y, float z);
        void set_target(glm::vec3 pos);
        void set_target(float x, float y, float z);
    };

    class Camera2D : public SoraEngine::Camera
    {
    private:
    public:
        Camera2D(float width, float height);
        Camera2D(float width, float height, float near, float far);
        ~Camera2D();

        virtual void create() override;
        virtual void update() override;
        virtual void update_projection() override;
        virtual void calculate_vectors() override;
    };

    class Camera3D : public SoraEngine::Camera
    {
    protected:
        float fov, a_ratio;

    public:
        Camera3D(float width, float height);
        Camera3D(float width, float height, float near, float far);
        Camera3D(float width, float height, float near, float far, float fov);
        ~Camera3D();

        virtual void create() override;
        virtual void update() override;
        virtual void update_projection() override;
        virtual void calculate_vectors() override;
    };

}