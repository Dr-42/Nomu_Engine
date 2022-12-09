#pragma once
#include "defines.h"
#include "ecs/component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Nomu
{
    class N_API Transform : public Component
    {
    public:
        Transform(Entity *entity);
        ~Transform();

        void Init() override;
        void Update(f32 dt) override;

        void SetPosition(glm::vec2 position);
        void SetPosition(f32 x, f32 y);
        void SetRotation(f32 rotation);
        void SetScale(glm::vec2 scale);
        void SetScale(f32 x, f32 y);

        glm::vec2 GetPosition();
        f32 GetRotation();
        glm::vec2 GetScale();

    private:
        glm::vec2 m_position;
        f32 m_rotation;
        glm::vec2 m_scale;
    };
}