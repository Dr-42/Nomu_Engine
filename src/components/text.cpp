#include "components/text.h"

Text::~Text()
{
    delete m_textRenderer;
}

Text::Text(std::string text, const char* fontPath, Shader* shader, int font_size, int screen_width, int screen_height, Transform* transform)
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

void Text::Init()
{
    m_textRenderer->Load(m_fontPath, m_font_size);
}

void Text::Update(float dt)
{
    if(isActivated)
    {
        m_textRenderer->RenderText(m_text, m_transform->GetPosition().x, m_transform->GetPosition().y, m_transform->GetScale().x, m_color);

    }

}

void Text::Destroy()
{

}
