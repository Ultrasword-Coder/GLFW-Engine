#pragma once
#include "component.hpp"

SoraComponent::Component::Component()
{
    this->id = SoraComponent::ComponentID++;
    char buf[50];
    snprintf(buf, sizeof(buf), "Comp-%llu", this->id);
    this->name = buf;
}

SoraComponent::Component::~Component() {}

void SoraComponent::Component::on_ready() {}
void SoraComponent::Component::update() {}
void SoraComponent::Component::clean() {}

std::string SoraComponent::Component::get_name()
{
    return this->name;
}
std::size_t SoraComponent::Component::get_id()
{
    return this->id;
}

// ----------------------- componenthandler ------------------ //

SoraComponent::ComponentHandler::ComponentHandler() {}
SoraComponent::ComponentHandler::~ComponentHandler() {}

void SoraComponent::ComponentHandler::add_component(SoraComponent::Component *comp)
{
    this->components.push_back(comp);
}

void SoraComponent::ComponentHandler::remove_component(std::string name)
{
    for (int i = 0; i < this->components.size(); i++)
    {
        if (this->components[i]->get_name() == name)
        {
            this->components.erase(this->components.begin() + i);
            break;
        }
    }
}

void SoraComponent::ComponentHandler::remove_component(std::size_t id)
{
    for (int i = 0; i < this->components.size(); i++)
    {
        if (this->components[i]->get_id() == id)
        {
            this->components.erase(this->components.begin() + i);
            break;
        }
    }
}

SoraComponent::Component *SoraComponent::ComponentHandler::get_component(std::string name)
{
    Component *comp;
    for (int i = 0; i < this->components.size(); i++)
    {
        if (this->components[i]->get_name() == name)
            return this->components.at(i);
    }
    return NULL;
}

SoraComponent::Component *SoraComponent::ComponentHandler::get_component(std::size_t id)
{
    Component *comp;
    for (int i = 0; i < this->components.size(); i++)
    {
        if (this->components[i]->get_id() == id)
            return this->components.at(i);
    }
    return NULL;
}

SoraComponent::Component *SoraComponent::ComponentHandler::get_at(int index)
{
    return this->components.at(index);
}

void SoraComponent::ComponentHandler::clean()
{
    for (int i = 0; i < this->components.size(); i++)
    {
        this->components[i]->clean();
    }
}
