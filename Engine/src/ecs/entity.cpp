#include "ecs/entity.h"

Nomu::Entity::Entity(std::string name)
{
    m_name = name;
    m_components = std::vector<Component*>();
    this->AddComponent(new Transform(this));
}

Nomu::Entity::~Entity()
{
    for (auto component : m_components)
    {
        delete component;
    }

    for (auto child : m_children)
    {
        delete child;
    }
}

void Nomu::Entity::Init()
{
    for (auto component : m_components)
    {
        component->Init();
    }

    for (auto child : m_children)
    {
        child->Init();
    }
}

void Nomu::Entity::Update(float dt)
{
    for (auto component : m_components)
    {
        component->Update(dt);
    }

    for (auto child : m_children)
    {
        child->Update(dt);
    }
}

void Nomu::Entity::Render()
{
    for (auto component : m_components)
    {
        component->Render();
    }

    for (auto child : m_children)
    {
        child->Render();
    }
}

Nomu::Entity* Nomu::Entity::Clone()
{
    Entity* clone = new Entity(m_name);

    for (auto component : m_components)
    {
        if(component->GetName() != "Transform")
        {
            component->SetEntity(clone);
            clone->AddComponent(component->Clone());
        }
    }

    for (auto child : m_children)
    {
        clone->AddChild(child->Clone());
    }

    return clone;
}


void Nomu::Entity::AddComponent(Component* component)
{
    m_components.push_back(component);
    component->SetEntity(this);
}

void Nomu::Entity::RemoveComponent(Component* component)
{
    m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
}

Nomu::Entity* Nomu::Entity::AddChild(Entity* child)
{
    child->SetParent(this);
    this->m_children.push_back(child);
    return child;
}

Nomu::Entity* Nomu::Entity::AddChild(Entity* child, const char* name)
{
    child->SetParent(this);
    child->m_name = name;
    m_children.push_back(child);
    return child;
}

Nomu::Entity* Nomu::Entity::AddChild(const char* name)
{
    Entity* child = new Entity(name);
    child->SetParent(this);
    m_children.push_back(child);
    return child;
}

Nomu::Entity* Nomu::Entity::GetChild(const char* name)
{
    for (auto child : m_children)
    {
        if (child->m_name == name)
        {
            return child;
        }
    }
    return nullptr;
}

std::vector<Nomu::Entity*> Nomu::Entity::GetChildren()
{
    return m_children;
}

void Nomu::Entity::RemoveChild(Nomu::Entity* child)
{
    m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
    child->Destroy();
}

void Nomu::Entity::RemoveChild(const char* name)
{
    for (auto child : m_children)
    {
        if (child->m_name == name)
        {
            m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
            child->Destroy();
            return;
        }
    }
}

void Nomu::Entity::SetParent(Nomu::Entity* parent)
{
    m_parent = parent;
}

Nomu::Entity* Nomu::Entity::GetParent()
{
    return m_parent;
}

void Nomu::Entity::Destroy()
{
    for (auto component : m_components)
    {
        component->Destroy();
    }

    for (auto child : m_children)
    {
        child->Destroy();
    }
}

std::vector<Nomu::Component*> Nomu::Entity::GetComponents()
{
    return m_components;
}


std::string Nomu::Entity::GetName()
{
    return m_name;
}

void Nomu::Entity::SetName(const char* name)
{
    m_name = name;
}

