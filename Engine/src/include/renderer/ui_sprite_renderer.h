#pragma once
#include "defines.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/texture.h"
#include "utils/shader.h"

namespace Nomu
{
    class N_API UI_SpriteRenderer
    {
    public:
        // Constructor (inits shaders/shapes)
        UI_SpriteRenderer(Shader *shader);
        // Destructor
        ~UI_SpriteRenderer();
        // Renders a defined quad textured with given sprite
        void DrawUISprite(Texture2D *texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), f32 rotate = 0.0f, f32 z = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    private:
        // Render state
        Shader *shader;
        u32 quadVAO;
        // Initializes and configures the quad's buffer and vertex attributes
        void initRenderData();
    };
}