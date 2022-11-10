#ifndef ENTITY_H
#define ENTITY_H

#include "ecs/component.h"

#include <vector>
#include <algorithm>

class Entity
{
public:
    Entity();
    ~Entity();

    void Init();
    void Update();
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    void Destroy();
    std::vector<Component*> GetComponents();

private:
    std::vector<Component*> m_components;
};

#endif