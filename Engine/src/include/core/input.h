#pragma once
#include "defines.h"
#include "core/app.h"

namespace Nomu
{
    class N_API Input
    {
    public:
        static Input &getInstance();
        static void SetApp(App& app);

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

        static void framebufferSizeCallbackImpl(GLFWwindow* window, int width, int height);
        static void keyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void cursorPositionCallbackImpl(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods);
    private:
        Input(void) = default;
        Input(Input const &);
        void operator=(Input const &);

        static App *mApp;
    };
}