#include "game.h"
#include "ecs/world.h"

#include <iostream>

Game::Game(unsigned int width, unsigned int height)
{
    this->Width = width;
    this->Height = height;
    this->MouseLeft = false;
    this->MouseRight = false;
    wireframe = false;
    this->MousePos = new glm::vec2(0.0f, 0.0f);
}

Game::~Game()
{
    delete MousePos;
    delete world;
}

void Game::Init(){
    // load shaders
#ifndef linux
    ResourceManager::LoadShader("F:/C++/Nomu_Engine/src/shaders/sprite_vert_shad.glsl", "F:/C++/Nomu_Engine/src/shaders/sprite_frag_shad.glsl", nullptr, "sprite");
    ResourceManager::LoadTexture("F:/C++/Nomu_Engine/src/textures/nomu.png", true, "sprite");
    
    const char* fontPath = "F:/C++/Nomu_Engine/src/fonts/OCRAEXT.TTF";
    ResourceManager::LoadShader("F:/C++/Nomu_Engine/src/shaders/text_vert_shad.glsl", "F:/C++/Nomu_Engine/src/shaders/text_frag_shad.glsl", nullptr, "text");
#else
    ResourceManager::LoadShader("/mnt/f/C++/Nomu_Engine/src/shaders/sprite_vert_shad.glsl", "/mnt/f/C++/Nomu_Engine/src/shaders/sprite_frag_shad.glsl", nullptr, "sprite");
    ResourceManager::LoadTexture("/mnt/f/C++/Nomu_Engine/src/textures/nomu.png", true, "sprite");

    const char* fontPath = "/mnt/f/C++/Nomu_Engine/src/fonts/OCRAEXT.TTF";
    ResourceManager::LoadShader("/mnt/f/C++/Nomu_Engine/src/shaders/text_vert_shad.glsl", "/mnt/f/C++/Nomu_Engine/src/shaders/text_frag_shad.glsl", nullptr, "text");
#endif  

    world = new World();
    MousePos = new glm::vec2(0.0f, 0.0f);

    world->GetEntityManager()->AddEntity("nomu");
    world->GetEntityManager()->GetEntity("nomu")->AddComponent(new Sprite(ResourceManager::GetTexture("sprite"), ResourceManager::GetShader("sprite"), Width, Height, world->GetEntityManager()->GetEntity("nomu")->GetComponent<Transform>()));
    world->GetEntityManager()->GetEntity("nomu")->AddComponent(new EventListener(world->GetEntityManager()->GetEntity("nomu")->GetComponent<Transform>(), MousePos, &MouseLeft, &MouseRight, Keys));

    world->GetEntityManager()->AddEntity("nomu1");
    world->GetEntityManager()->GetEntity("nomu1")->AddComponent(new Sprite(ResourceManager::GetTexture("sprite"), ResourceManager::GetShader("sprite"), this->Width, this->Height, world->GetEntityManager()->GetEntity("nomu1")->GetComponent<Transform>()));
    world->GetEntityManager()->GetEntity("nomu1")->AddComponent(new EventListener(world->GetEntityManager()->GetEntity("nomu1")->GetComponent<Transform>(), MousePos, &MouseLeft, &MouseRight, Keys));

    world->GetEntityManager()->AddEntity("hello_text");
    world->GetEntityManager()->GetEntity("hello_text")->AddComponent( new Text("Hello!", fontPath, ResourceManager::GetShader("text"), 24, this->Width, this->Height, world->GetEntityManager()->GetEntity("hello_text")->GetComponent<Transform>()));

    world->GetEntityManager()->AddEntity("engine_text");
    world->GetEntityManager()->GetEntity("engine_text")->AddComponent( new Text("Hello from NOMU Engine", fontPath, ResourceManager::GetShader("text"), 24, this->Width, this->Height, world->GetEntityManager()->GetEntity("engine_text")->GetComponent<Transform>()));

    world->Init();
    
    world->GetEntityManager()->GetEntity("nomu")->GetComponent<Transform>()->SetPosition(glm::vec2(400.0f, 400.0f));
    world->GetEntityManager()->GetEntity("nomu")->GetComponent<Transform>()->SetScale(glm::vec2(400.0f, 400.0f));

    world->GetEntityManager()->GetEntity("hello_text")->GetComponent<Transform>()->SetPosition(glm::vec2(300, 100));
    world->GetEntityManager()->GetEntity("hello_text")->GetComponent<Transform>()->SetScale(glm::vec2(2, 1.0));

    world->GetEntityManager()->GetEntity("engine_text")->GetComponent<Transform>()->SetPosition(glm::vec2(450, 770));
    world->GetEntityManager()->GetEntity("engine_text")->GetComponent<Transform>()->SetScale(glm::vec2(1.0, 1.0));
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

    world->Update(dt);
    if(world->GetEntityManager()->GetEntity("nomu")->GetComponent<EventListener>()->isLeftClicked()){
        std::cout << "Left Clicked" << std::endl;
    }
    if(world->GetEntityManager()->GetEntity("nomu")->GetComponent<EventListener>()->isRightClicked()){
        std::cout << "Right Clicked" << std::endl;
    }

    if(world->GetEntityManager()->GetEntity("nomu")->GetComponent<EventListener>()->isLeftClickedandHeld()){
        world->GetEntityManager()->GetEntity("nomu")->GetComponent<Transform>()->SetPosition(*MousePos);
    }

    if(world->GetEntityManager()->GetEntity("nomu1")->GetComponent<EventListener>()->isRightClickedandHeld()){
        world->GetEntityManager()->GetEntity("nomu1")->GetComponent<Transform>()->SetPosition(*MousePos);
    }

}