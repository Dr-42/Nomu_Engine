#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component();
    
    virtual ~Component();

    virtual void Init();
    virtual void Update();
    virtual void Destroy();
};

#endif