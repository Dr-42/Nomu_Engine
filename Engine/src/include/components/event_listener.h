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
        bool isLeftClickedandHeld();
        bool isRightClickedandHeld();
        bool isHovered();

    private:
        Transform *m_transform;
        App* m_app;
        float m_leftClickTime, m_rightClickTime;
        bool m_leftClickHeld;
        bool m_rightClickHeld;

        bool isMouseOver();
    };
}