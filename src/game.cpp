#include "game.h"

#include "utils/scene_manager.h"

#include <iostream>

Game::Game(unsigned int width, unsigned int height)
{
    this->Width = width;
    this->Height = height;
    this->MouseLeft = false;
    this->MouseRight = false;
    wireframe = false;
    this->MousePos = new glm::vec2(0.0f, 0.0f);
    root = new Entity("root");
}

Game::~Game()
{
    delete MousePos;
    delete root;
}

void Game::Init(){

    SceneManager sceneManager;
    root = sceneManager.LoadScene("assets/scenes/scene1.nsc", Width, Height, &MouseLeft, &MouseRight, MousePos, Keys);
   
    root->Init();
}

void Game::ProcessInput(float dt)
{
   if(this->Keys[GLFW_KEY_SPACE]){
       wireframe = !wireframe;
       if(wireframe){
           glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       }else{
           glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       }
   }
}

void Game::Update(float dt)
{

    root->Update(dt);
    if(root->GetChild("nomu")->GetComponent<EventListener>()->isLeftClicked()){
        std::cout << "Left Clicked" << std::endl;
    }
    if(root->GetChild("nomu")->GetComponent<EventListener>()->isRightClicked()){
        std::cout << "Right Clicked" << std::endl;
    }

    if(root->GetChild("nomu")->GetComponent<EventListener>()->isLeftClickedandHeld()){
        root->GetChild("nomu")->GetComponent<Transform>()->SetPosition(*MousePos);
    }

    if(root->GetChild("nomu1")->GetComponent<EventListener>()->isRightClickedandHeld()){
        root->GetChild("nomu1")->GetComponent<Transform>()->SetPosition(*MousePos);
    }

    std::string fps = "FPS: " + std::to_string(1.0f / dt);
    root->GetChild("fps")->GetComponent<Text>()->SetText(fps);

}

void Game::Render()
{
    root->Render();
}