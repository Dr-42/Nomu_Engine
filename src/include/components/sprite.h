#include <iostream>

#include "ecs/component.h"
#include "components/transform.h"
#include "texture.h"
#include "sprite_renderer.h"
#include "shader.h"
#include "resource_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Sprite : public Component
{
public:
    Sprite();
    ~Sprite();

    void Init(int width, int height, Texture2D texture, Shader shader, int screen_width, int screen_height, Transform* transform);
    void Update();
    void Destroy();

    void SetTexture(const char* texturePath);
    void SetTexture(Texture2D* texture);

    void SetShader(Shader* shader, glm::vec2 size);

    Texture2D* GetTexture();
    SpriteRenderer* GetSpriteRenderer();
    Shader* GetShader();

    bool isActivated = false;

private:

    void m_ConfigureShader();

    Transform* m_transform; 
    Texture2D* m_texture;
    SpriteRenderer* m_spriteRenderer;
    Shader* m_shader;
    glm::vec2 m_size;
    int srceenWidth, screenHeight;
}; 