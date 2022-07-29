#pragma once

#include <memory.h>
#include <algorithm>
#include <string>
#include <vector>

namespace SoraComponent
{
    static std::size_t ComponentID = 1;

    class Component
    {
    private:
        std::size_t id;
        std::string name;

    public:
        Component();
        ~Component();

        virtual void on_ready();
        virtual void update();
        virtual void clean();

        std::string get_name();
        std::size_t get_id();
    };

    class ComponentHandler
    {
    private:
        std::vector<Component *> components;

    public:
        ComponentHandler();
        ~ComponentHandler();

        void add_component(Component *comp);
        void remove_component(std::string name);
        void remove_component(std::size_t id);

        SoraComponent::Component *get_component(std::string name);
        SoraComponent::Component *get_component(std::size_t id);

        SoraComponent::Component *get_at(int index);

        void clean();
    };

}
