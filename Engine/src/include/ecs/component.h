#pragma once
#include "defines.h"
#include <string>

namespace Nomu
{
    class Entity;
    class N_API Component
    {
    public:
        Component();

        virtual ~Component();

        virtual void Init();
        virtual void Update(float dt);
        virtual void Render();
        virtual void Destroy();

        virtual Component *Clone();
        Entity *GetEntity() const { return m_entity; }
        void SetEntity(Entity *entity);
        std::string GetName() const { return m_name; }
        bool active;

    protected:
        std::string m_name;
        Entity *m_entity;
    };
}