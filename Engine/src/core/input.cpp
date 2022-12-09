#include "core/input.h"

Nomu::App *Nomu::Input::mApp = nullptr;

Nomu::Input &Nomu::Input::getInstance()
{
    static Input instance;
    return instance;
}

void Nomu::Input::SetApp(App* app)
{
    mApp = app;
}


void Nomu::Input::framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height)
{
    getInstance().framebufferSizeCallbackImpl(window, width, height);
}

void Nomu::Input::keyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mode)
{
    getInstance().keyCallbackImpl(window, key, scancode, action, mode);
}

void Nomu::Input::cursorPositionCallback(GLFWwindow* window, f64 xpos, f64 ypos)
{
    getInstance().cursorPositionCallbackImpl(window, xpos, ypos);
}

void Nomu::Input::mouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods)
{
    getInstance().mouseButtonCallbackImpl(window, button, action, mods);
}


void Nomu::Input::framebufferSizeCallbackImpl(GLFWwindow* window, i32 width, i32 height)
{
    glViewport(0, 0, width, height);
}

void Nomu::Input::keyCallbackImpl(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mode)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            mApp->Keys[key] = true;
        else if (action == GLFW_RELEASE)
            mApp->Keys[key] = false;
    }
}

void Nomu::Input::cursorPositionCallbackImpl(GLFWwindow* window, f64 xpos, f64 ypos)
{
    mApp->mousePos.x = xpos;
    mApp->mousePos.y = ypos;
}

void Nomu::Input::mouseButtonCallbackImpl(GLFWwindow* window, i32 button, i32 action, i32 mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        mApp->mouseLeft = true;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        mApp->mouseLeft = false;

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        mApp->mouseRight = true;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        mApp->mouseRight = false;
}

glm::vec2 Nomu::Input::GetMousePos()
{
    return mApp->mousePos;
}