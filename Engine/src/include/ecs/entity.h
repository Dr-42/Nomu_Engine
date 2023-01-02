#pragma once
#include "defines.h"
#include "ecs/component.h"
#include "components/transform.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>
namespace Nomu
{
    class N_API Entity
    {
    public:
        Entity(std::string name);
        ~Entity();

        void Init();
        void Update(f32 dt);
        void Render();
        Entity *Clone();

        void AddComponent(Component *component);
        void RemoveComponent(Component *component);

        Entity *AddChild(Entity *child);
        Entity *AddChild(Entity *child, std::string name);
        Entity *AddChild(std::string name);

        Entity *GetChild(std::string name);
        std::vector<Entity*> GetChildren();

        void RemoveChild(Entity* child);
        void RemoveChild(std::string name);
        void DestroyChild(Entity* child);
        void DestroyChild(std::string name);

        void SetParent(Entity* parent);
        Entity *GetParent();

        void Destroy();
        std::vector<Component*> GetComponents();
        std::string GetName();
        void SetName(std::string name);

        // generic function to get components
        template <typename T>
        T *GetComponent()
        {

            for (u64 i = 0; i < m_components.size(); i++)
            {
                if (T *component = dynamic_cast<T*>(m_components[i]))
                {
                    return component;
                }
            }
            exit(1);
        }

    private:
        std::string m_name;
        std::vector<Component*> m_components;
        std::vector<Entity*> m_children;
        glm::vec3 m_positionOffsetFromParent;
        f32 m_rotationOffsetFromParent;
        Entity *m_parent;
    };
}