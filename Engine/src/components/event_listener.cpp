#include "components/event_listener.h"
#include "ecs/entity.h"

Nomu::EventListener::EventListener(App* app)
{
    m_app = app;
    m_leftClickTime = 0.0f;
    m_rightClickTime = 0.0f;
    m_name = "EventListener";
}

Nomu::EventListener::~EventListener()
{
}

void Nomu::EventListener::Init()
{
    m_transform = GetEntity()->GetComponent<Transform>();
}

void Nomu::EventListener::Update(float dt)
{
    if (m_leftClickTime > 0.0f)
    {
        if(m_leftClickTime > dt)
        {
            m_leftClickTime -= dt;
        }
        else
        {
            m_leftClickTime = 0.0f;
        }
        
    } 

    if (m_rightClickTime > 0.0f)
    {
        if(m_rightClickTime > dt)
        {
            m_rightClickTime -= dt;
        }
        else
        {
            m_rightClickTime = 0.0f;
        }
        
    }

    if (!m_app->mouseLeft)
    {
        m_leftClickHeld = false;
    }

    if (!m_app->mouseRight)
    {
        m_rightClickHeld = false;
    }
}

Nomu::EventListener* Nomu::EventListener::Clone()
{
    EventListener* eventListener = new EventListener(m_app);
    return eventListener;
}

bool Nomu::EventListener::isLeftClickedandHeld()
{
    if (isMouseOver() && m_app->mouseLeft)
    {
        return true;
    }
    return false;   
}

bool Nomu::EventListener::isRightClickedandHeld()
{
    if(isMouseOver() && m_app->mouseRight)
    {
        return true;
    }
    return false;
}

bool Nomu::EventListener::isHovered()
{
    return isMouseOver();
}

bool Nomu::EventListener::isLeftClicked()
{
    if (isMouseOver() && m_app->mouseLeft && m_leftClickTime == 0.0f && !m_leftClickHeld)
    {
        m_leftClickTime = 0.1f;
        m_leftClickHeld = true;
        return true;
    }
    return false;
}

bool Nomu::EventListener::isRightClicked()
{
    if (isMouseOver() && m_app->mouseRight && m_rightClickTime == 0.0f && !m_rightClickHeld)
    {
        m_rightClickTime = 0.1f;
        m_rightClickHeld = true;
        return true;
    }
    return false;
}

bool Nomu::EventListener::isMouseOver()
{
    //the top left corner is (0,0)
    //the bottom right corner is (m_game->Width, m_game->Height)
    //the mouse position is (m_game->MousePos.x, m_game->MousePos.y)
    //the entity position is (m_transform->GetPosition().x, m_transform->GetPosition().y)
    //the entity size is (m_transform->GetScale().x, m_transform->GetScale().y)

    //check if the mouse is over the entity
    if (m_app->mousePos.x >= m_transform->GetPosition().x - m_transform->GetScale().x / 2 &&
        m_app->mousePos.x <= m_transform->GetPosition().x + m_transform->GetScale().x / 2 &&
        m_app->mousePos.y >= m_transform->GetPosition().y - m_transform->GetScale().y / 2 &&
        m_app->mousePos.y <= m_transform->GetPosition().y + m_transform->GetScale().y / 2)
    {
        return true;
    }
    return false;
}