#include <core/input.h>
#include <components/script.h>
#include <components/everything.h>
#include <ecs/entity.h>


class NomuScript : public Nomu::Script
{
    void Update(float dt)
    {
        if(GetEntity()->GetComponent<Nomu::EventListener>()->isLeftClickedandHeld()){
            GetEntity()->GetComponent<Nomu::Transform>()->SetPosition(Nomu::Input::GetMousePos());
        }

        if(GetEntity()->GetComponent<Nomu::EventListener>()->isRightClicked()){
            std::cout << "Right Clicked" << std::endl;
        }
        if(GetEntity()->GetComponent<Nomu::EventListener>()->isLeftClicked()){
            std::cout << "Left Clicked" << std::endl;
        }
    }
};

bool dummy = Nomu::Script::Register<NomuScript>("NomuScript");