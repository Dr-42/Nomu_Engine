#include "components/script.h"

std::map<std::string, Nomu::Script*> Nomu::Script::m_scripts;

void Nomu::Script::Init()
{
}

void Nomu::Script::Update(float dt)
{
}

void Nomu::Script::Render()
{
}

Nomu::Script* Nomu::Script::Create(std::string name)
    {
        if(m_scripts.find(name) != m_scripts.end())
        {
            return m_scripts[name];
        }
        else{
            Nomu::Logger::Error("Failed to create script: {0} does not exist" + name);
            return nullptr;
        }
    }