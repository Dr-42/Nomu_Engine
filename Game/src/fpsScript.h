#include <core/input.h>
#include <components/script.h>
#include <components/everything.h>
#include <ecs/entity.h>


class FpsScript : public Nomu::Script
{
    void Update(float dt)
    {
        std::string fps = "FPS: " + std::to_string(1.0f / dt);
        GetEntity()->GetComponent<Nomu::Text>()->SetText(fps);
    }

    FpsScript* Clone()
    {
        return new FpsScript();
    }
};

bool dummy2 = Nomu::Script::Register<FpsScript>("FpsScript");