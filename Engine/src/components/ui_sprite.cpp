#include "components/ui_sprite.h"
#include "ecs/entity.h"

Nomu::UI_Sprite::~UI_Sprite()
{
    delete m_spriteRenderer;
}

Nomu::UI_Sprite::UI_Sprite(Nomu::Texture2D* texture, glm::vec4 color, Nomu::Shader* shader, Nomu::App* app)
{
    m_texture = texture;
    m_color = color;
    m_shader = shader;
    m_app = app;
    m_name = "UISprite";
    m_spriteRenderer = new Nomu::UI_SpriteRenderer(m_shader);
}

Nomu::UI_Sprite::UI_Sprite(Nomu::Texture2D* texture, Nomu::Shader* shader, Nomu::App* app)
{
    m_texture = texture;
    m_color = glm::vec4(1.0f);
    m_shader = shader;
    m_app = app;
    m_name = "UISprite";
    m_spriteRenderer = new Nomu::UI_SpriteRenderer(m_shader);
}

void Nomu::UI_Sprite::Init()
{
    m_ConfigureShader();
}

void Nomu::UI_Sprite::Render()
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

void Nomu::UI_Sprite::Update(f32 dt)
{
}

Nomu::UI_Sprite* Nomu::UI_Sprite::Clone()
{
    UI_Sprite* sprite = new UI_Sprite(m_texture, m_color, m_shader, m_app);
    return sprite;
}

void Nomu::UI_Sprite::SetTexture(std::string texturePath)
{
    ResourceManager::LoadTexture(texturePath, true, "face");
    std::cout << "Loaded texture: " << texturePath << std::endl;
}

void Nomu::UI_Sprite::SetTexture(Nomu::Texture2D* texture)
{
    m_texture = texture;
}

void Nomu::UI_Sprite::SetColor(glm::vec4 color)
{
    m_color = color;
}

void Nomu::UI_Sprite::SetZ(f32 z)
{
    m_z = z;
}

f32 Nomu::UI_Sprite::GetZ()
{
    return m_z;
}

void Nomu::UI_Sprite::SetShader(Nomu::Shader* shader, glm::vec2 size)
{
    m_shader = shader;
    m_size = size;
}


Nomu::Texture2D* Nomu::UI_Sprite::GetTexture()
{
    return m_texture;
}

Nomu::UI_SpriteRenderer* Nomu::UI_Sprite::GetUI_SpriteRenderer()
{
    return m_spriteRenderer;
}

Nomu::Shader* Nomu::UI_Sprite::GetShader()
{
    return m_shader;
}

void Nomu::UI_Sprite::m_ConfigureShader()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<f32>(m_app->WIDTH), 
        static_cast<f32>(m_app->HEIGHT), 0.0f, -100.0f, 100.0f);
    //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (f32)m_app->WIDTH / (f32)m_app->HEIGHT, 0.1f, 100.0f);
    this->m_shader->Use().SetInteger("image", 0);
    this->m_shader->SetMatrix4("projection", projection);
}