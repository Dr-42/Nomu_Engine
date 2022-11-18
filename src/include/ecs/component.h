#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component();
    
    virtual ~Component();

    virtual void Init();
    virtual void Update(float dt);
    virtual void Destroy();

    virtual Component* Clone();
    const char* GetName() const { return m_name; }
protected:
    const char* m_name;
};

#endif