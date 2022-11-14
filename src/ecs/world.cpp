#include "ecs/world.h"

World::World()
{
    m_entityManager = new EntityManager();
}

World::~World()
{
    delete m_entityManager;
}

void World::Init()
{
    m_entityManager->Init();
}

void World::Update(float dt)
{
    m_entityManager->Update(dt);
}

EntityManager* World::GetEntityManager() const
{
    return m_entityManager;
}
