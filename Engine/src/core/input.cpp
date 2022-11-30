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


void Nomu::Input::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    getInstance().framebufferSizeCallbackImpl(window, width, height);
}

void Nomu::Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    getInstance().keyCallbackImpl(window, key, scancode, action, mode);
}

void Nomu::Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    getInstance().cursorPositionCallbackImpl(window, xpos, ypos);
}

void Nomu::Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    getInstance().mouseButtonCallbackImpl(window, button, action, mods);
}


void Nomu::Input::framebufferSizeCallbackImpl(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Nomu::Input::keyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            mApp->Keys[key] = true;
        else if (action == GLFW_RELEASE)
            mApp->Keys[key] = false;
    }
}

void Nomu::Input::cursorPositionCallbackImpl(GLFWwindow* window, double xpos, double ypos)
{
    mApp->mousePos.x = xpos;
    mApp->mousePos.y = ypos;
}

void Nomu::Input::mouseButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods)
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