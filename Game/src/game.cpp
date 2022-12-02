#include "game.h"
#include "nomuScript.h"
#include "nomu1Script.h"
#include "fpsScript.h"

#include <GLFW/glfw3.h>
#include <utils/scene_manager.h>
#include <iostream>

MyGame::MyGame()
{
    wireframe = false;
    root = new Nomu::Entity("root");
}

MyGame::~MyGame()
{
    delete root;
}

void MyGame::SetApp(Nomu::App& app)
{
    mApp = &app;
}

void MyGame::Init(){

    Nomu::SceneManager sceneManager;
    root = sceneManager.LoadScene("../assets/scenes/scene1.nsc", mApp->WIDTH, mApp->HEIGHT, &mApp->mouseLeft, &mApp->mouseRight, &mApp->mousePos, mApp->Keys);

    root->Init();
}

void MyGame::ProcessInput(float dt)
{
   if(mApp->Keys[GLFW_KEY_SPACE]){
       wireframe = !wireframe;
       if(wireframe){
           glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       }else{
           glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       }
   }

   if(mApp->Keys[GLFW_KEY_ESCAPE]){
       glfwSetWindowShouldClose(mApp->window, true);
   }
}

void MyGame::Update(float dt)
{

    root->Update(dt);
}

void MyGame::Render()
{
    root->Render();
}