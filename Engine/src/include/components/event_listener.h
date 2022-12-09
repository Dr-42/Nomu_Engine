#pragma once
#include "defines.h"
#include "core/app.h"
#include "ecs/component.h"
#include "components/transform.h"
namespace Nomu
{
    class N_API EventListener : public Component
    {
    public:
        EventListener(App* app);
        virtual ~EventListener();

        void Init() override;
        void Update(f32 dt) override;
        EventListener* Clone() override;

        bl isLeftClicked();
        bl isRightClicked();
        bl wasLeftClickReleased();
        bl wasRightClickReleased();
        bl isLeftClickedandHeld();
        bl isRightClickedandHeld();
        bl isHovered();
        bl mouseEntered();
        bl mouseExited();
        bl isLeftClickedInside();
        bl isRightClickedInside();

        bl isKeyPressed(i32 key);
        bl isKeyReleased(i32 key);

    private:
        Transform *m_transform;
        App* m_app;
        bl m_leftClicked_curr, m_leftClicked_prev;
        bl m_rightClicked_curr, m_rightClicked_prev;
        f32 m_mouseX, m_mouseY;
        bl currMouseOver, prevMouseOver;
        bl mouseLeftClickedInside, mouseRightClickedInside;
        bl isMouseOver();
    };
}