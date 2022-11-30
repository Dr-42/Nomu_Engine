#include "core/engine.h"

Nomu::Engine::Engine(App* app)
{
    this->mApp = app;
    if(mApp->window != nullptr){
        Nomu::Logger::Error("Window is not null");
    }
}

Nomu::Engine::~Engine()
{
}

void Nomu::Engine::setGame(Game* game)
{
    this->mGame = game;
}

bool Nomu::Engine::Init(){
    if (!glfwInit())
    {
        Nomu::Logger::Error("Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    mApp->window = glfwCreateWindow(mApp->WIDTH, mApp->HEIGHT, mApp->title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(mApp->window);

    // glew: load all OpenGL function pointers
    GLenum err = glewInit();
    if (glewInit() != GLEW_OK)
    {
        Nomu::Logger::Error("Failed to initialize GLEW error");
        return false;
    }

    Nomu::Input::getInstance();
    Nomu::Input::SetApp(mApp);

    glfwSetKeyCallback(mApp->window, Nomu::Input::keyCallback);
    glfwSetCursorPosCallback(mApp->window, Nomu::Input::cursorPositionCallback);
    glfwSetMouseButtonCallback(mApp->window, Nomu::Input::mouseButtonCallback);
    glfwSetFramebufferSizeCallback(mApp->window, Nomu::Input::framebufferSizeCallback);

    // OpenGL configuration
    glViewport(mApp->x, mApp->y, mApp->WIDTH, mApp->HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mGame->Init();
    return true;
}

bool Nomu::Engine::Run(){
    while (!glfwWindowShouldClose(mApp->window))
    {
        currentFrame = glfwGetTime();
        mApp->deltaTime = currentFrame - mApp->lastFrame;
        glfwPollEvents();
        mGame->ProcessInput(mApp->deltaTime);
        mGame->Update(mApp->deltaTime);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mGame->Render();
        glfwSwapBuffers(mApp->window);

        mApp->lastFrame = currentFrame;
    }
    return true;
}

void Nomu::Engine::Shutdown(){
    glfwTerminate();
}

