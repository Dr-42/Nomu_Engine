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
        void Update(float dt) override;

        void SetPosition(glm::vec2 position);
        void SetPosition(float x, float y);
        void SetRotation(float rotation);
        void SetScale(glm::vec2 scale);
        void SetScale(float x, float y);

        glm::vec2 GetPosition();
        float GetRotation();
        glm::vec2 GetScale();

    private:
        glm::vec2 m_position;
        float m_rotation;
        glm::vec2 m_scale;
    };
}