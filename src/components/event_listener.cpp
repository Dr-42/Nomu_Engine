#include "components/event_listener.h"

EventListener::EventListener(Transform* transform, glm::vec2* mousePos, bool* mouseLeft, bool* mouseRight, bool* keys)
{
    m_transform = transform;
    m_mousePos = mousePos;
    m_mouseLeft = mouseLeft;
    m_mouseRight = mouseRight;
    m_keys = keys;
}

EventListener::~EventListener()
{
}

bool EventListener::isLeftClicked()
{
    if (isMouseOver() && *m_mouseLeft)
    {
        return true;
    }
    return false;   
}

bool EventListener::isRightClicked()
{
    if(isMouseOver() && *m_mouseRight)
    {
        return true;
    }
}

bool EventListener::isHovered()
{
    return isMouseOver();
}

bool EventListener::isMouseOver()
{
    //the top left corner is (0,0)
    //the bottom right corner is (m_game->Width, m_game->Height)
    //the mouse position is (m_game->MousePos.x, m_game->MousePos.y)
    //the entity position is (m_transform->GetPosition().x, m_transform->GetPosition().y)
    //the entity size is (m_transform->GetScale().x, m_transform->GetScale().y)

    //check if the mouse is over the entity
    if (m_mousePos->x >= m_transform->GetPosition().x - m_transform->GetScale().x / 2 &&
        m_mousePos->x <= m_transform->GetPosition().x + m_transform->GetScale().x / 2 &&
        m_mousePos->y >= m_transform->GetPosition().y - m_transform->GetScale().y / 2 &&
        m_mousePos->y <= m_transform->GetPosition().y + m_transform->GetScale().y / 2)
    {
        return true;
    }
}

