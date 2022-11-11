#ifndef ENTITY_H
#define ENTITY_H

#include "ecs/component.h"
#include "components/transform.h"
#include "components/sprite.h"

#include <vector>
#include <algorithm>

class Entity
{
public:
    Entity(const char* name);
    ~Entity();

    void Init();
    void Update();
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    void Destroy();
    std::vector<Component*> GetComponents();
    Transform* GetTransform();
    const char* GetName();

    void AddSprite(Sprite* sprite);

private:
    const char* m_name;
    std::vector<Component*> m_components;
    Transform* m_transform;
};

#endif