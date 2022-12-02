#include "game.h"
#include "nomuScript.h"
#include "nomu1Script.h"
#include "fpsScript.h"
#include <core/input.h>

#include <utils/scene_manager.h>

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

    if(mApp->Keys[NOMU_KEY_ESCAPE]){
        mApp->Close();
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