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

    Entity* AddEntity(Entity* entity, const char* name);
    void RemoveEntity(Entity* entity);
    std::vector<Entity*> GetEntities();
    Entity* GetEntity(const char* name);

private:
    std::vector<Entity*> m_entities;
};

#endif