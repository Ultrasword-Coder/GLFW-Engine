#pragma once

#include <memory.h>
#include <string.h>
#include <vector>

#include "../components/component.hpp"

namespace SoraEngine
{
    static std::size_t GameObjectID = 1;

    class GameObject
    {
    private:
        std::size_t id;
        std::string name;

    public:
        GameObject();
        ~GameObject();

        virtual void on_ready();
        virtual void update();
        virtual void render();
        virtual void clean();

        std::string get_name();
        std::size_t get_id();
    };
}