#include "core/app.h"

void Nomu::App::Close()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
}