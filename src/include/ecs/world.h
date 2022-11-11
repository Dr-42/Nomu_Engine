#ifndef WORLD_H
#define WORLD_H

#include "ecs/entity_manager.h"
#include "ecs/entity.h"
#include "ecs/component.h"

#include <vector>

class World
{
public:
    World();
    ~World();

    void Init();
    void Update();

    EntityManager* GetEntityManager() const;

    EntityManager* m_entityManager;
};

#endif