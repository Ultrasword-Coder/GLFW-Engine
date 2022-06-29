#pragma once

#include "component.hpp"

Sora::Component::Component()
{
    this->id = Sora::component_counter++;
}

Sora::Component::~Component() {}

void Sora::Component::on_ready() {}
void Sora::Component::update() {}