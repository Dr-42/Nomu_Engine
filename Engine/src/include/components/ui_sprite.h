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
    class N_API UI_Sprite : public Component
    {
    public:
        UI_Sprite(Texture2D *texture, glm::vec4 color, Shader *shader, App *app);
        UI_Sprite(Texture2D *texture, Shader *shader, App *app);
        ~UI_Sprite();

        void Init() override;
        void Update(f32 dt) override;
        void Render() override;
        UI_Sprite *Clone() override;

        void SetTexture(std::string texturePath);
        void SetTexture(Texture2D *texture);

        void SetColor(glm::vec4 color);

        void SetZ(f32 z);
        f32 GetZ();

        void SetShader(Shader *shader, glm::vec2 size);

        Texture2D *GetTexture();
        UI_SpriteRenderer *GetUI_SpriteRenderer();
        Shader *GetShader();

    private:
        void m_ConfigureShader();

        Texture2D *m_texture;
        UI_SpriteRenderer *m_spriteRenderer;
        Shader *m_shader;
        glm::vec2 m_size;
        glm::vec4 m_color;
        App* m_app;
        f32 m_z = 0.0f;
    };
}