#include <core/input.h>
#include <components/script.h>
#include <components/everything.h>
#include <ecs/entity.h>


class Nomu1Script : public Nomu::Script
{
    void Update(float dt)
    {
        if(GetEntity()->GetComponent<Nomu::EventListener>()->isRightClickedandHeld()){
            GetEntity()->GetComponent<Nomu::Transform>()->SetPosition(Nomu::Input::GetMousePos());
        }
    }
};

bool dummy1 = Nomu::Script::Register<Nomu1Script>("Nomu1Script");