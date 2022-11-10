#include "components/sprite.h"

Sprite::~Sprite()
{
}

Sprite::Sprite(int width, int height, Texture2D texture, Shader shader, int screen_width, int screen_height, Transform* transform)
{
    m_texture = &texture;
    m_shader = &shader;
    m_size = glm::vec2(width, height);
    srceenWidth = screen_width;
    screenHeight = screen_height;
    m_spriteRenderer = new SpriteRenderer(m_shader);
    m_transform = transform;
    isActivated = true;
}

void Sprite::Init()
{
    m_ConfigureShader();
}

void Sprite::Update()
{
    if(isActivated)
    {
        m_spriteRenderer->DrawSprite(m_texture, m_transform->GetScale(), m_transform->GetPosition(), m_transform->GetRotation());
    }

}

void Sprite::Destroy()
{

}

void Sprite::SetTexture(const char* texturePath)
{
    ResourceManager::LoadTexture(texturePath, true, "face");
    std::cout << "Loaded texture: " << texturePath << std::endl;
}

void Sprite::SetTexture(Texture2D* texture)
{
    m_texture = texture;
}

void Sprite::SetShader(Shader* shader, glm::vec2 size)
{
    m_shader = shader;
    m_size = size;
}


Texture2D* Sprite::GetTexture()
{
    return m_texture;
}

SpriteRenderer* Sprite::GetSpriteRenderer()
{
    return m_spriteRenderer;
}

Shader* Sprite::GetShader()
{
    return m_shader;
}

void Sprite::m_ConfigureShader()
{
    m_shader->Use();
    m_shader->SetInteger("image", 0);
    m_shader->SetVector2f("screenSize", glm::vec2(srceenWidth, screenHeight));
    m_shader->SetVector2f("size", m_size);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->srceenWidth), 
        static_cast<float>(this->screenHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);
}






