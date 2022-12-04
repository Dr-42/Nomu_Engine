#include "components/sprite.h"
#include "ecs/entity.h"

Nomu::Sprite::~Sprite()
{
    delete m_spriteRenderer;
}

Nomu::Sprite::Sprite(Nomu::Texture2D* texture, glm::vec4 color, Nomu::Shader* shader, Nomu::App* app)
{
    m_texture = texture;
    m_color = color;
    m_shader = shader;
    m_app = app;
    m_name = "Sprite";
    m_spriteRenderer = new Nomu::SpriteRenderer(m_shader);
}

Nomu::Sprite::Sprite(Nomu::Texture2D* texture, Nomu::Shader* shader, Nomu::App* app)
{
    m_texture = texture;
    m_color = glm::vec4(1.0f);
    m_shader = shader;
    m_app = app;
    m_name = "Sprite";
    m_spriteRenderer = new Nomu::SpriteRenderer(m_shader);
}

void Nomu::Sprite::Init()
{
    m_ConfigureShader();
}

void Nomu::Sprite::Render()
{
    if(active)
    {
        m_spriteRenderer->DrawSprite(
            m_texture,
            GetEntity()->GetComponent<Transform>()->GetPosition(),
            GetEntity()->GetComponent<Transform>()->GetScale(),
            GetEntity()->GetComponent<Transform>()->GetRotation(),
            m_color);
    }

}

void Nomu::Sprite::Update(float dt)
{
}

void Nomu::Sprite::Destroy()
{

}

Nomu::Sprite* Nomu::Sprite::Clone()
{
    Sprite* sprite = new Sprite(m_texture, m_color, m_shader, m_app);
    return sprite;
}

void Nomu::Sprite::SetTexture(const char* texturePath)
{
    ResourceManager::LoadTexture(texturePath, true, "face");
    std::cout << "Loaded texture: " << texturePath << std::endl;
}

void Nomu::Sprite::SetTexture(Nomu::Texture2D* texture)
{
    m_texture = texture;
}

void Nomu::Sprite::SetColor(glm::vec4 color)
{
    m_color = color;
}

void Nomu::Sprite::SetShader(Nomu::Shader* shader, glm::vec2 size)
{
    m_shader = shader;
    m_size = size;
}


Nomu::Texture2D* Nomu::Sprite::GetTexture()
{
    return m_texture;
}

Nomu::SpriteRenderer* Nomu::Sprite::GetSpriteRenderer()
{
    return m_spriteRenderer;
}

Nomu::Shader* Nomu::Sprite::GetShader()
{
    return m_shader;
}

void Nomu::Sprite::m_ConfigureShader()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_app->WIDTH), 
        static_cast<float>(m_app->HEIGHT), 0.0f, -1.0f, 1.0f);
    this->m_shader->Use().SetInteger("image", 0);
    this->m_shader->SetMatrix4("projection", projection);
}