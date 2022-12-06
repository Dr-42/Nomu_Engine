#include "ecs/component.h"
#include <iostream>

Nomu::Component::Component()
{
}

Nomu::Component::~Component()
{
}

void Nomu::Component::Init()
{
}

void Nomu::Component::Update(float dt)
{
}

void Nomu::Component::Render()
{
}

void Nomu::Component::Destroy()
{
}

void Nomu::Component::SetEntity(Nomu::Entity *entity)
{
    m_entity = entity;
}

Nomu::Component* Nomu::Component::Clone()
{
    std::cerr << "Component::Clone() called with unspecified component" << std::endl;
    return nullptr;
}