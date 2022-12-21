#include "components/ui_sprite.h"
#include "ecs/entity.h"

Nomu::UISprite::~UISprite()
{
    delete m_spriteRenderer;
}

Nomu::UISprite::UISprite(Nomu::Texture2D* texture, glm::vec4 color, Nomu::Shader* shader, Nomu::App* app)
{
    m_texture = texture;
    m_color = color;
    m_shader = shader;
    m_app = app;
    m_name = "UISprite";
    m_spriteRenderer = new Nomu::UIUISpriteRenderer(m_shader);
}

Nomu::UISprite::UISprite(Nomu::Texture2D* texture, Nomu::Shader* shader, Nomu::App* app)
{
    m_texture = texture;
    m_color = glm::vec4(1.0f);
    m_shader = shader;
    m_app = app;
    m_name = "UISprite";
    m_spriteRenderer = new Nomu::UIUISpriteRenderer(m_shader);
}

void Nomu::UISprite::Init()
{
    m_ConfigureShader();
}

void Nomu::UISprite::Render()
{
    if(active)
    {
        m_spriteRenderer->DrawUISprite(
            m_texture,
            GetEntity()->GetComponent<Transform>()->GetPosition(),
            GetEntity()->GetComponent<Transform>()->GetScale(),
            GetEntity()->GetComponent<Transform>()->GetRotation(),
            m_z,
            m_color);
    }

}

void Nomu::UISprite::Update(f32 dt)
{
}

Nomu::UISprite* Nomu::UISprite::Clone()
{
    UISprite* sprite = new UISprite(m_texture, m_color, m_shader, m_app);
    return sprite;
}

void Nomu::UISprite::SetTexture(std::string texturePath)
{
    ResourceManager::LoadTexture(texturePath, true, "face");
    std::cout << "Loaded texture: " << texturePath << std::endl;
}

void Nomu::UISprite::SetTexture(Nomu::Texture2D* texture)
{
    m_texture = texture;
}

void Nomu::UISprite::SetColor(glm::vec4 color)
{
    m_color = color;
}

void Nomu::UISprite::SetZ(f32 z)
{
    m_z = z;
}

f32 Nomu::UISprite::GetZ()
{
    return m_z;
}

void Nomu::UISprite::SetShader(Nomu::Shader* shader, glm::vec2 size)
{
    m_shader = shader;
    m_size = size;
}


Nomu::Texture2D* Nomu::UISprite::GetTexture()
{
    return m_texture;
}

Nomu::UIUISpriteRenderer* Nomu::UISprite::GetUIUISpriteRenderer()
{
    return m_spriteRenderer;
}

Nomu::Shader* Nomu::UISprite::GetShader()
{
    return m_shader;
}

void Nomu::UISprite::m_ConfigureShader()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<f32>(m_app->WIDTH), 
        static_cast<f32>(m_app->HEIGHT), 0.0f, -100.0f, 100.0f);
    //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (f32)m_app->WIDTH / (f32)m_app->HEIGHT, 0.1f, 100.0f);
    this->m_shader->Use().SetInteger("image", 0);
    this->m_shader->SetMatrix4("projection", projection);
}