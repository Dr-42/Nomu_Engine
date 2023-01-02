#pragma once
#include "defines.h"
#include "core/app.h"
#include <iostream>

#include "ecs/component.h"
#include "components/transform.h"
#include "utils/texture.h"
#include "renderer/ui_sprite_renderer.h"
#include "utils/shader.h"
#include "utils/resource_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Nomu
{
    class N_API UISprite : public Component
    {
    public:
        UISprite(Texture2D *texture, glm::vec4 color, Shader *shader, App *app);
        UISprite(Texture2D *texture, Shader *shader, App *app);
        ~UISprite();

        void Init() override;
        void Update(f32 dt) override;
        void Render() override;
        UISprite *Clone() override;

        void SetTexture(std::string texturePath);
        void SetTexture(Texture2D *texture);

        void SetColor(glm::vec4 color);

        void SetZ(f32 z);
        f32 GetZ();

        void SetShader(Shader *shader, glm::vec2 size);

        Texture2D *GetTexture();
        UIUISpriteRenderer *GetUIUISpriteRenderer();
        Shader *GetShader();

    private:
        void m_ConfigureShader();

        Texture2D *m_texture;
        UIUISpriteRenderer *m_spriteRenderer;
        Shader *m_shader;
        glm::vec2 m_size;
        glm::vec4 m_color;
        App* m_app;
        f32 m_z = 0.0f;
    };
}