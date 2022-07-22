#pragma once

#include <vector>
#include <memory.h>
#include <algorithm>
#include <array>
#include <bitset>

namespace SoraCore
{
    long long component_counter = 0;

    class Component;
    class GameObject;

    using ComponentID = std::size_t;

    inline ComponentID get_component_id();

    template <typename T>
    inline ComponentID get_component_id() noexcept;

    constexpr std::size_t maxComponents = 32;

    using ComponentBitSet = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component *, maxComponents>;

    class Component
    {
    private:
    public:
        GameObject *owner;

        virtual void init();
        virtual void update();

        virtual ~Component();
    };

    using GameObjectID = std::size_t;

    inline GameObjectID get_gameobject_id()
    {
        static GameObjectID last_gameobject_id;
        return last_gameobject_id++;
    }

    template <typename T>
    inline GameObjectID get_gameobject_id()
    {
        static GameObjectID gameobjectTypeID = get_gameobject_id();
        return gameobjectTypeID();
    }

    class GameObject
    {
    private:
    public:
        std::vector<Component *> components;
    };

}
