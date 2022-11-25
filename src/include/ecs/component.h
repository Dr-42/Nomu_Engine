#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Entity;

class Component
{
public:
    Component();
    
    virtual ~Component();

    virtual void Init();
    virtual void Update(float dt);
    virtual void Render();
    virtual void Destroy();

    virtual Component* Clone();
    Entity* GetEntity() const { return m_entity; }
    void SetEntity(Entity* entity) { m_entity = entity; }
    std::string GetName() const { return m_name; }
    bool active;
protected:
    std::string m_name;
    Entity* m_entity;
};

#endif