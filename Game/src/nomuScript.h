#include <core/input.h>
#include <components/script.h>
#include <components/everything.h>
#include <ecs/entity.h>


class NomuScript : public Nomu::Script
{
    void Update(float dt)
    {
        if(GetEntity()->GetComponent<Nomu::EventListener>()->isLeftClickedandHeld()){
            GetEntity()->GetComponent<Nomu::UI_Sprite>()->SetZ(-1.0f);
            GetEntity()->GetComponent<Nomu::Transform>()->SetPosition(Nomu::Input::GetMousePos());
        }
        if(GetEntity()->GetComponent<Nomu::EventListener>()->wasLeftClickReleased()){
            GetEntity()->GetComponent<Nomu::UI_Sprite>()->SetZ(1.0f);
        }
    }

    NomuScript* Clone()
    {
        return new NomuScript();
    }
};

bool dummy = Nomu::Script::Register<NomuScript>("NomuScript");