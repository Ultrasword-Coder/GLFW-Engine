#pragma once
#include "gameobject.hpp"

inline SoraCore::ComponentID SoraCore::get_component_id()
{
    static ComponentID last_component_id = 0;
    return last_component_id++;
}

template <typename T>
inline SoraCore::ComponentID SoraCore::get_component_id() noexcept
{
    static ComponentID componentTypeID = get_component_id();
    return componentTypeID();
}
