#include "ecs/entity_manager.h"

EntityManager::EntityManager()
{
    m_entities = std::vector<Entity*>();
}

EntityManager::~EntityManager()
{
    for (auto entity : m_entities)
    {
        delete entity;
    }
}

void EntityManager::Init()
{
    for (auto entity : m_entities)
    {
        entity->Init();
    }
}

void EntityManager::Update(float dt)
{
    for (auto entity : m_entities)
    {
        entity->Update(dt);
    }
}

Entity* EntityManager::AddEntity(const char* name)
{
    Entity* entity = new Entity(name);
    m_entities.push_back(entity);
    return entity;
}

Entity* EntityManager::GetEntity(const char* name)
{
    for (auto entity : m_entities)
    {
        if (entity->GetName() == name)
        {
            return entity;
        }
    }
    return nullptr;
}

void EntityManager::RemoveEntity(Entity* entity)
{
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
    delete entity;
}

std::vector<Entity*> EntityManager::GetEntities()
{
    return m_entities;
}