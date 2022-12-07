#include <core/input.h>
#include <components/script.h>
#include <components/everything.h>
#include <ecs/entity.h>
#include <core/input.h>


class Nomu1Script : public Nomu::Script
{
    void Update(float dt)
    {
        if(GetEntity()->GetComponent<Nomu::EventListener>()->isRightClickedandHeld()){
            GetEntity()->GetComponent<Nomu::Sprite>()->SetZ(-1.0f);
            GetEntity()->GetComponent<Nomu::Transform>()->SetPosition(Nomu::Input::GetMousePos());
        }
        if(GetEntity()->GetComponent<Nomu::EventListener>()->wasRightClickReleased()){
            GetEntity()->GetComponent<Nomu::Sprite>()->SetZ(1.0f);
        }
        if(GetEntity()->GetComponent<Nomu::EventListener>()->isKeyPressed(NOMU_KEY_SPACE)){
            GetEntity()->GetComponent<Nomu::Sprite>()->SetZ(GetEntity()->GetComponent<Nomu::Sprite>()->GetZ() + -0.001f);
        }
        if(GetEntity()->GetComponent<Nomu::EventListener>()->isKeyPressed(NOMU_KEY_A)){
            GetEntity()->GetComponent<Nomu::Sprite>()->SetZ(GetEntity()->GetComponent<Nomu::Sprite>()->GetZ() + -0.001f);
        }
    }
};

bool dummy1 = Nomu::Script::Register<Nomu1Script>("Nomu1Script");