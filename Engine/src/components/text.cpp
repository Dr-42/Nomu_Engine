#include "components/text.h"
#include "ecs/entity.h"

Nomu::Text::~Text()
{
    delete m_textRenderer;
}

Nomu::Text::Text(std::string text, std::string fontPath, Shader *shader, int font_size, int screen_width, int screen_height, Nomu::Transform *transform)
{
    m_text = text;
    m_font_size = font_size;
    screenWidth = screen_width;
    screenHeight = screen_height;
    m_transform = transform;
    isActivated = true;
    m_color = glm::vec3(1.0f, 1.0f, 1.0f);

    m_textRenderer = new TextRenderer(screenWidth, screenHeight, shader);

    m_fontPath = fontPath;
    m_name = "Text";
}

void Nomu::Text::Init()
{
    m_textRenderer->Load(m_fontPath, m_font_size);
}

void Nomu::Text::Update(float dt)
{
}

void Nomu::Text::Render()
{
    if (isActivated)
    {
        m_textRenderer->RenderText(m_text, m_transform->GetPosition().x, m_transform->GetPosition().y, m_transform->GetScale().x, m_color);
    }
}

void Nomu::Text::Destroy()
{
}

Nomu::Text *Nomu::Text::Clone()
{
    Text *text = new Text(m_text, m_fontPath, m_textRenderer->GetShader(), m_font_size, screenWidth, screenHeight, m_entity->GetComponent<Transform>());
    return text;
}

void Nomu::Text::SetText(std::string text)
{
    m_text = text;
}

void Nomu::Text::SetFontSize(int font_size)
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
