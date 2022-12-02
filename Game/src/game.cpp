#include "game.h"
#include "nomuScript.h"
#include <GLFW/glfw3.h>
#include <utils/scene_manager.h>
#include <components/script.h>
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

    Nomu::Entity* nomu = root->GetChild("nomu");
    Nomu::Component* scr = dynamic_cast<Nomu::Component*>(Nomu::Script::Create("NomuScript"));
    nomu->AddComponent(scr);
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
}

void MyGame::Update(float dt)
{

    root->Update(dt);

    if(root->GetChild("nomu1")->GetComponent<Nomu::EventListener>()->isRightClickedandHeld()){
        root->GetChild("nomu1")->GetComponent<Nomu::Transform>()->SetPosition(mApp->mousePos);
    }

    std::string fps = "FPS: " + std::to_string(1.0f / dt);
    root->GetChild("fps")->GetComponent<Nomu::Text>()->SetText(fps);

}

void MyGame::Render()
{
    root->Render();
}