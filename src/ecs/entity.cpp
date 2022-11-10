#include "ecs/entity.h"

Entity::Entity()
{
    m_components = std::vector<Component*>();
}

Entity::~Entity()
{
    for (auto component : m_components)
    {
        delete component;
    }
}

void Entity::Init()
{
    for (auto component : m_components)
    {
        component->Init();
    }
}

void Entity::Update()
{
    for (auto component : m_components)
    {
        component->Update();
    }
}

void Entity::AddComponent(Component* component)
{
    m_components.push_back(component);
}

void Entity::RemoveComponent(Component* component)
{
    m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
}

void Entity::Destroy()
{
    for (auto component : m_components)
    {
        component->Destroy();
    }
}

std::vector<Component*> Entity::GetComponents()
{
    return m_components;
}


