#include "components/sprite.h"
#include "ecs/entity.h"

Nomu::Sprite::~Sprite()
{
    delete m_spriteRenderer;
}

Nomu::Sprite::Sprite(Nomu::Texture2D* texture, glm::vec4 color, Nomu::Shader* shader, int screen_width, int screen_height, Nomu::Transform* transform)
{
    m_texture = texture;
    m_color = color;
    m_shader = shader;
    m_transform = transform;
    m_size = m_transform->GetScale();
    screenWidth = screen_width;
    screenHeight = screen_height;
    m_spriteRenderer = new SpriteRenderer(m_shader);
    active = true;
    m_name = "Sprite";
}

Nomu::Sprite::Sprite(Nomu::Texture2D* texture, Nomu::Shader* shader, int screen_width, int screen_height, Nomu::Transform* transform)
{
    m_texture = texture;
    m_color = glm::vec4(1.0f);
    m_shader = shader;
    m_transform = transform;
    m_size = m_transform->GetScale();
    screenWidth = screen_width;
    screenHeight = screen_height;
    m_spriteRenderer = new SpriteRenderer(m_shader);
    active = true;
    m_name = "Sprite";
}

void Nomu::Sprite::Init()
{
    m_ConfigureShader();
    m_entity = m_transform->GetEntity();
}

void Nomu::Sprite::Render()
{
    if(active)
    {
        m_spriteRenderer->DrawSprite(m_texture, m_transform->GetPosition(), m_transform->GetScale(), m_transform->GetRotation(), m_color);
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
    Sprite* sprite = new Sprite(m_texture, m_color, m_shader, screenWidth, screenHeight, m_entity->GetComponent<Transform>());
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
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->screenWidth), 
        static_cast<float>(this->screenHeight), 0.0f, -1.0f, 1.0f);
    this->m_shader->Use().SetInteger("image", 0);
    this->m_shader->SetMatrix4("projection", projection);
}