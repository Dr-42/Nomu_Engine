#include "renderer/ui_sprite_renderer.h"


Nomu::UIUISpriteRenderer::UIUISpriteRenderer(Nomu::Shader* shader)
{
    this->shader = shader;
    this->initRenderData();
}

Nomu::UIUISpriteRenderer::~UIUISpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Nomu::UIUISpriteRenderer::DrawUISprite(Nomu::Texture2D* texture, glm::vec2 position, glm::vec2 size, f32 rotate, f32 z, glm::vec3 color)
{
    // prepare transformations
    this->shader->Use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    position -= glm::vec2(size.x / 2, size.y / 2);

    model = glm::translate(model, glm::vec3(position, 10*z));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    this->shader->SetMatrix4("model", model);
    this->shader->SetMatrix4("view", view);

    // render textured quad
    this->shader->SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture->Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Nomu::UIUISpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    u32 VBO;
    f32 vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
