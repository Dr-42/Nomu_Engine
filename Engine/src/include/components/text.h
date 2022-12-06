#pragma once
#include "defines.h"
#include "core/app.h"
#include <iostream>
#include <string>

#include "ecs/component.h"
#include "components/transform.h"
#include "utils/texture.h"
#include "renderer/text_renderer.h"
#include "utils/shader.h"
#include "utils/resource_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Nomu
{
    class N_API Text : public Component
    {
    public:
        Text(std::string text, std::string fontPath, Shader *shader, int font_size, App* app);
        ~Text();

        void Init() override;
        void Update(float dt) override;
        void Render() override;
        void Destroy();
        Text *Clone() override;

        void SetText(std::string text);
        void SetFontSize(int font_size);
        void SetColor(glm::vec3 color);
        void SetFontPath(const char *fontPath);

        TextRenderer *GetTextRenderer();
    private:
        TextRenderer *m_textRenderer;
        App* m_app;
        std::string m_text;
        int m_font_size;
        glm::vec3 m_color;
        std::string m_fontPath;
    };
}