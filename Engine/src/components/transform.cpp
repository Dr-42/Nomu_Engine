#include "components/transform.h"
#include <iostream>

Nomu::Transform::Transform(Nomu::Entity* entity)
{
    m_entity = entity;
    m_position = glm::vec2(200.0f, 200.0f);
    m_rotation = 0.0f;
    m_scale = glm::vec2(100.0f, 100.0f);
    m_name = "Transform";
}

Nomu::Transform::~Transform()
{
}

void Nomu::Transform::Init()
{
}

void Nomu::Transform::Update(f32 dt)
{
}

void Nomu::Transform::SetPosition(glm::vec2 position)
{
    m_position = position;
}

void Nomu::Transform::SetPosition(f32 x, f32 y)
{
    m_position = glm::vec2(x, y);
}

void Nomu::Transform::SetRotation(f32 rotation)
{
    m_rotation = rotation;
}

void Nomu::Transform::SetScale(glm::vec2 scale)
{
    m_scale = scale;
}

void Nomu::Transform::SetScale(f32 x, f32 y)
{
    m_scale = glm::vec2(x, y);
}

glm::vec2 Nomu::Transform::GetPosition()
{
    return m_position;
}

f32 Nomu::Transform::GetRotation()
{
    return m_rotation;
}

glm::vec2 Nomu::Transform::GetScale()
{
    return m_scale;
}

void Nomu::Transform::Translate(glm::vec2 translation)
{
    m_position += translation;
}

void Nomu::Transform::Translate(f32 x, f32 y)
{
    m_position += glm::vec2(x, y);
}

void Nomu::Transform::Rotate(f32 rotation)
{
    m_rotation += rotation;
}

void Nomu::Transform::Scale(glm::vec2 scale)
{
    m_scale += scale;
}

void Nomu::Transform::Scale(f32 x, f32 y)
{
    m_scale += glm::vec2(x, y);
}