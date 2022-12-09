#include "components/event_listener.h"
#include "ecs/entity.h"

Nomu::EventListener::EventListener(App *app)
{
    m_app = app;
    m_name = "EventListener";
}

Nomu::EventListener::~EventListener()
{
}

void Nomu::EventListener::Init()
{
    m_transform = GetEntity()->GetComponent<Transform>();
}

void Nomu::EventListener::Update(f32 dt)
{
    if (active)
    {
        m_leftClicked_prev = m_leftClicked_curr;
        m_rightClicked_prev = m_rightClicked_curr;
        m_leftClicked_curr = m_app->mouseLeft;
        m_rightClicked_curr = m_app->mouseRight;
        m_mouseX = m_app->mousePos.x;
        m_mouseY = m_app->mousePos.y;
        prevMouseOver = currMouseOver;
        currMouseOver = isMouseOver();
    }
}

Nomu::EventListener *Nomu::EventListener::Clone()
{
    EventListener *eventListener = new EventListener(m_app);
    return eventListener;
}

bl Nomu::EventListener::isLeftClickedandHeld()
{
    if (active)
    {
        if(isMouseOver() && m_leftClicked_curr && m_leftClicked_prev && !mouseEntered())
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::isRightClickedandHeld()
{
    if (active)
    {
        if(isMouseOver() && m_rightClicked_curr && m_rightClicked_prev)
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::isHovered()
{
    if (active)
    {
        return isMouseOver();
    }
    return false;
}

bl Nomu::EventListener::isLeftClicked()
{
    if (active)
    {
        if(isMouseOver() && m_leftClicked_curr && !m_leftClicked_prev)
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::isRightClicked()
{
    if (active)
    {
        if(isMouseOver() && m_rightClicked_curr && !m_rightClicked_prev)
        {
            return true;
        }
    }
    return false;
}

bl Nomu::EventListener::wasLeftClickReleased()
{
    if (active)
    {
        if(isMouseOver() && !m_leftClicked_curr && m_leftClicked_prev)
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::wasRightClickReleased()
{
    if (active)
    {
        if(isMouseOver() && !m_rightClicked_curr && m_rightClicked_prev)
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::isMouseOver()
{
    // the top left corner is (0,0)
    // the bottom right corner is (m_game->Width, m_game->Height)
    // the mouse position is (m_game->MousePos.x, m_game->MousePos.y)
    // the entity position is (m_transform->GetPosition().x, m_transform->GetPosition().y)
    // the entity size is (m_transform->GetScale().x, m_transform->GetScale().y)
    if (active)
    {
        // check if the mouse is over the entity
        if (m_mouseX >= m_transform->GetPosition().x - m_transform->GetScale().x / 2 &&
            m_mouseX <= m_transform->GetPosition().x + m_transform->GetScale().x / 2 &&
            m_mouseY >= m_transform->GetPosition().y - m_transform->GetScale().y / 2 &&
            m_mouseY <= m_transform->GetPosition().y + m_transform->GetScale().y / 2)
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::mouseEntered()
{
    if (active)
    {
        if (currMouseOver && !prevMouseOver)
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::mouseExited()
{
    if (active)
    {
        if(!currMouseOver && prevMouseOver)
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::isLeftClickedInside()
{
    if (active)
    {
        if(isLeftClicked() && isMouseOver() && !m_leftClicked_prev)
        {
            mouseLeftClickedInside = true;
            return true;
        }
        else if (isLeftClicked() && isMouseOver() && m_leftClicked_prev)
        {
            if(mouseLeftClickedInside)
            {
                return true;
            }
            else
            {
                return false;
            }
            return false;
        }
        else{
            mouseLeftClickedInside = false;
            return false;
        }
    }
    return false;
}

bl Nomu::EventListener::isRightClickedInside()
{
    if (active)
    {
        if(isRightClicked() && isMouseOver() && !m_rightClicked_prev)
        {
            mouseRightClickedInside = true;
            return true;
        }
        else if (isRightClicked() && isMouseOver() && m_rightClicked_prev)
        {
            if(mouseRightClickedInside)
            {
                return true;
            }
            else
            {
                return false;
            }
            return false;
        }
        else{
            mouseRightClickedInside = false;
            return false;
        }
    }
    return false;
}

bl Nomu::EventListener::isKeyPressed(i32 key)
{
    if (active)
    {
        if (m_app->Keys[key])
        {
            return true;
        }
        return false;
    }
    return false;
}

bl Nomu::EventListener::isKeyReleased(i32 key)
{
    if (active)
    {
        if (!m_app->Keys[key])
        {
            return true;
        }
        return false;
    }
    return false;
}