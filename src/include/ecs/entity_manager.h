#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "ecs/entity.h"

#include <vector>
#include <algorithm>

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void Init();
    void Update();

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    std::vector<Entity*> GetEntities();

private:
    std::vector<Entity*> m_entities;
};

#endif