#include "components/script.h"

std::map<std::string, Nomu::Script*> Nomu::Script::m_scripts;

void Nomu::Script::Init()
{
    m_name = "Script";
}

void Nomu::Script::Update(f32 dt)
{
}

void Nomu::Script::Render()
{
}

Nomu::Script* Nomu::Script::Create(std::string name)
    {
        if(m_scripts.find(name) != m_scripts.end())
        {
            return m_scripts[name]->Clone();
        }
        else{
            Nomu::Logger::Error("Failed to create script: " + name + "does not exist");
            return nullptr;
        }
    }