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

void Nomu::Entity::Update(f32 dt)
{
    for (auto component : m_components)
    {
        if(component != nullptr)
            component->Update(dt);
        else{
            std::cout << "Component is null" << std::endl;
            RemoveComponent(component);
        }
    }

    for (auto child : m_children)
    {
        if(child != nullptr){
            child->Update(dt);
        }
        else{
            std::cout << "Child is null" << std::endl;
            RemoveChild(child);
        }
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
            Component* comp = component->Clone();
            comp->SetEntity(clone);
            clone->AddComponent(comp);
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

Nomu::Entity* Nomu::Entity::AddChild(Entity* child, std::string name)
{
    child->SetParent(this);
    child->m_name = name;
    m_children.push_back(child);
    return child;
}

Nomu::Entity* Nomu::Entity::AddChild(std::string name)
{
    Entity* child = new Entity(name);
    child->SetParent(this);
    m_children.push_back(child);
    return child;
}

Nomu::Entity* Nomu::Entity::GetChild(std::string name)
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
}

void Nomu::Entity::RemoveChild(std::string name)
{
    for (auto child : m_children)
    {
        if (child->m_name == name)
        {
            m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
            return;
        }
    }
}

void Nomu::Entity::DestroyChild(Nomu::Entity* child)
{
    child->Destroy();
    m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
}

void Nomu::Entity::DestroyChild(std::string name)
{
    for (auto child : m_children)
    {
        if (child->m_name == name)
        {
            child->Destroy();
            m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
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
    m_components.clear();

    for (auto child : m_children)
    {
        child->Destroy();
    }
    m_children.clear();
    m_parent->RemoveChild(this);
    delete this;
}

std::vector<Nomu::Component*> Nomu::Entity::GetComponents()
{
    return m_components;
}


std::string Nomu::Entity::GetName()
{
    return m_name;
}

void Nomu::Entity::SetName(std::string name)
{
    m_name = name;
}

