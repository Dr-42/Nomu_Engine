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

void EntityManager::Update()
{
    for (auto entity : m_entities)
    {
        entity->Update();
    }
}

void EntityManager::AddEntity(Entity* entity)
{
    m_entities.push_back(entity);
}

void EntityManager::RemoveEntity(Entity* entity)
{
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
}

std::vector<Entity*> EntityManager::GetEntities()
{
    return m_entities;
}