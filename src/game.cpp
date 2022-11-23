#include "game.h"

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
    // load shaders
    ResourceManager::LoadShader("assets/shaders/sprite_vert_shad.glsl", "assets/shaders/sprite_frag_shad.glsl", nullptr, "sprite");
    ResourceManager::LoadTexture("assets/textures/nomu.png", true, "sprite");

    const char* fontPath = "assets/fonts/OCRAEXT.TTF";
    ResourceManager::LoadShader("assets/shaders/text_vert_shad.glsl", "assets/shaders/text_frag_shad.glsl", nullptr, "text");

    MousePos = new glm::vec2(0.0f, 0.0f);

    root->AddChild("nomu");
    root->GetChild("nomu")->AddComponent(new Sprite(ResourceManager::GetTexture("sprite"), ResourceManager::GetShader("sprite"), Width, Height, root->GetChild("nomu")->GetComponent<Transform>()));
    root->GetChild("nomu")->AddComponent(new EventListener(root->GetChild("nomu")->GetComponent<Transform>(), MousePos, &MouseLeft, &MouseRight, Keys));

    Entity* nomu1 = root->GetChild("nomu")->Clone();
    nomu1->SetName("nomu1");
    root->AddChild(nomu1);


    root->AddChild("hello_text");
    root->GetChild("hello_text")->AddComponent( new Text("Hello!", fontPath, ResourceManager::GetShader("text"), 24, this->Width, this->Height, root->GetChild("hello_text")->GetComponent<Transform>()));

    root->AddChild("engine_text");
    root->GetChild("engine_text")->AddComponent( new Text("Hello from NOMU Engine", fontPath, ResourceManager::GetShader("text"), 24, this->Width, this->Height, root->GetChild("engine_text")->GetComponent<Transform>()));

    Entity* fps = root->GetChild("engine_text")->Clone();
    fps->SetName("fps");
    root->AddChild(fps);
    
    root->GetChild("nomu")->GetComponent<Transform>()->SetPosition(glm::vec2(400.0f, 400.0f));
    root->GetChild("nomu")->GetComponent<Transform>()->SetScale(glm::vec2(400.0f, 400.0f));

    root->GetChild("hello_text")->GetComponent<Transform>()->SetPosition(glm::vec2(300, 100));
    root->GetChild("hello_text")->GetComponent<Transform>()->SetScale(glm::vec2(2, 1.0));

    root->GetChild("engine_text")->GetComponent<Transform>()->SetPosition(glm::vec2(450, 770));
    root->GetChild("engine_text")->GetComponent<Transform>()->SetScale(glm::vec2(1.0, 1.0));

    root->GetChild("fps")->GetComponent<Transform>()->SetPosition(glm::vec2(10, 10));
    root->GetChild("fps")->GetComponent<Transform>()->SetScale(glm::vec2(1.0, 1.0));

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