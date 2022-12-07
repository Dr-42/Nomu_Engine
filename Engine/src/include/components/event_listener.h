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
        void Update(float dt) override;
        EventListener* Clone() override;

        bool isLeftClicked();
        bool isRightClicked();
        bool wasLeftClickReleased();
        bool wasRightClickReleased();
        bool isLeftClickedandHeld();
        bool isRightClickedandHeld();
        bool isHovered();
        bool mouseEntered();
        bool mouseExited();
        bool isLeftClickedInside();
        bool isRightClickedInside();

        bool isKeyPressed(int key);
        bool isKeyReleased(int key);

    private:
        Transform *m_transform;
        App* m_app;
        bool m_leftClicked_curr, m_leftClicked_prev;
        bool m_rightClicked_curr, m_rightClicked_prev;
        float m_mouseX, m_mouseY;
        bool currMouseOver, prevMouseOver;
        bool mouseLeftClickedInside, mouseRightClickedInside;
        bool isMouseOver();
    };
}