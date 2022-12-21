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
            GetEntity()->GetComponent<Nomu::UISprite>()->SetZ(-1.0f);
            GetEntity()->GetComponent<Nomu::Transform>()->SetPosition(Nomu::Input::GetMousePos());
        }
        if(GetEntity()->GetComponent<Nomu::EventListener>()->wasRightClickReleased()){
            GetEntity()->GetComponent<Nomu::UISprite>()->SetZ(1.0f);
        }
        //WASD controls
        if(Nomu::Input::isKeyPressed(NOMU_KEY_W)){
            GetEntity()->GetComponent<Nomu::Transform>()->Translate(0.0f, -100.0f * dt);
        }
        if(Nomu::Input::isKeyPressed(NOMU_KEY_A)){
            GetEntity()->GetComponent<Nomu::Transform>()->Translate(-100.0f * dt, 0.0f);
        }
        if(Nomu::Input::isKeyPressed(NOMU_KEY_S)){
            GetEntity()->GetComponent<Nomu::Transform>()->Translate(0.0f, 100.0f * dt);
        }
        if(Nomu::Input::isKeyPressed(NOMU_KEY_D)){
            GetEntity()->GetComponent<Nomu::Transform>()->Translate(100.0f * dt, 0.0f);
        }
    }

    Nomu1Script* Clone()
    {
        return new Nomu1Script();
    }
};

bool dummy1 = Nomu::Script::Register<Nomu1Script>("Nomu1Script");