#pragma once
#include "defines.h"
#include "core/app.h"
#include <iostream>

#include "ecs/component.h"
#include "components/transform.h"
#include "utils/texture.h"
#include "renderer/sprite_renderer.h"
#include "utils/shader.h"
#include "utils/resource_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Nomu
{
    class N_API Sprite : public Component
    {
    public:
        Sprite(Texture2D *texture, glm::vec4 color, Shader *shader, App *app);
        Sprite(Texture2D *texture, Shader *shader, App *app);
        ~Sprite();

        void Init() override;
        void Update(float dt) override;
        void Render() override;
        void Destroy();
        Sprite *Clone() override;

        void SetTexture(const char *texturePath);
        void SetTexture(Texture2D *texture);

        void SetColor(glm::vec4 color);

        void SetZ(float z);
        float GetZ();

        void SetShader(Shader *shader, glm::vec2 size);

        Texture2D *GetTexture();
        SpriteRenderer *GetSpriteRenderer();
        Shader *GetShader();

    private:
        void m_ConfigureShader();

        Texture2D *m_texture;
        SpriteRenderer *m_spriteRenderer;
        Shader *m_shader;
        glm::vec2 m_size;
        glm::vec4 m_color;
        App* m_app;
        float m_z = 0.0f;
    };
}