#include "components/text.h"
#include "ecs/entity.h"

Nomu::Text::~Text()
{
    delete m_textRenderer;
}

Nomu::Text::Text(std::string text, std::string fontPath, Shader *shader, u32 font_size, App* app)
{
    m_text = text;
    m_font_size = font_size;
    m_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_app = app;

    m_textRenderer = new TextRenderer(m_app->WIDTH, m_app->HEIGHT, shader);

    m_fontPath = fontPath;
    m_name = "Text";
}

void Nomu::Text::Init()
{
    m_textRenderer->Load(m_fontPath, m_font_size);
}

void Nomu::Text::Update(f32 dt)
{
}

void Nomu::Text::Render()
{
    if (active)
    {
        m_textRenderer->RenderText(
            m_text,
            GetEntity()->GetComponent<Transform>()->GetPosition().x,
            GetEntity()->GetComponent<Transform>()->GetPosition().y,
            GetEntity()->GetComponent<Transform>()->GetScale().x,
            m_color);    }
}

Nomu::Text *Nomu::Text::Clone()
{
    Text *text = new Text(m_text, m_fontPath, m_textRenderer->GetShader(), m_font_size, m_app);
    return text;
}

void Nomu::Text::SetText(std::string text)
{
    m_text = text;
}

void Nomu::Text::SetFontSize(u32 font_size)
{
    m_font_size = font_size;
}

void Nomu::Text::SetColor(glm::vec3 color)
{
    m_color = color;
}

void Nomu::Text::SetFontPath(const char *fontPath)
{
    m_fontPath = fontPath;
}

Nomu::TextRenderer *Nomu::Text::GetTextRenderer()
{
    return m_textRenderer;
}
