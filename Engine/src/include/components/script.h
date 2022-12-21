#pragma once
#include <map>
#include <typeinfo>
#include "core/logger.h"
#include "ecs/component.h"
namespace Nomu
{
    class N_API Script : public Component
    {
    public:
        Script() = default;
        virtual ~Script() = default;

        virtual void Init();
        virtual void Update(f32 dt);
        virtual void Render();

        template <typename T>
        static bl Register(std::string name)
        {
            T* script = new T();
            if(dynamic_cast<Script*>(script) == nullptr){
                Logger::Error("Script::Register: Script is not derived from Script class");
                return false;
            }
            m_scripts[name] = script;
            return true;
        }
        static Script* Create(std::string name);
        virtual Script* Clone() = 0;
    private:
        static std::map<std::string, Script *> m_scripts;
        Entity* mParent;
    };
}