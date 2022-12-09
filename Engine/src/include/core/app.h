#pragma once
#include "defines.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace Nomu
{
    class N_API App
    {
    public:
        GLFWwindow *window;
        std::string title;
        i32 WIDTH;
        i32 HEIGHT;
        i32 x, y;
        bl Keys[1024];
        bl mouseLeft, mouseRight;
        glm::vec2 mousePos;
        f32 deltaTime;
        f32 lastFrame;

        void Close();
    };
}