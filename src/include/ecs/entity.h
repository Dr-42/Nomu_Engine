#ifndef ENTITY_H
#define ENTITY_H

#include "ecs/component.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "components/text.h"

#include <vector>
#include <algorithm>
#define quote(x) #x

class Entity
{
public:
    Entity(const char* name);
    ~Entity();

    void Init();
    void Update(float dt);
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    void Destroy();
    std::vector<Component*> GetComponents();
    const char* GetName();

    //generic function to get components
    template <typename T>
    T* GetComponent()
    {

        for (long long unsigned int i = 0; i < m_components.size(); i++)
        {
            if (T* component = dynamic_cast<T*>(m_components[i]))
            {
                return component;
            }
        }
        std::cout << "Component " << quote(T) << " not found" << std::endl;
        return nullptr;
    }

private:
    const char *m_name;
    std::vector<Component *> m_components;
};

#endif