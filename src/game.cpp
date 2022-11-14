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

    entity = world->GetEntityManager()->AddEntity("nomu");
    sprite = new Sprite(ResourceManager::GetTexture("face"), ResourceManager::GetShader("sprite"), this->Width, this->Height, entity->GetComponent<Transform>());
    entity->AddComponent(sprite);
    sprite->SetTexture(ResourceManager::GetTexture("sprite"));
    evln = new EventListener(entity->GetComponent<Transform>(), MousePos, &MouseLeft, &MouseRight, Keys);
    entity->AddComponent(evln);

    entity1 = world->GetEntityManager()->AddEntity("nomu2");
    Text *text = new Text("Hello!", fontPath, ResourceManager::GetShader("text"), 24, this->Width, this->Height, entity1->GetComponent<Transform>());
    entity1->AddComponent(text);

    entity2 = world->GetEntityManager()->AddEntity("nomu3");
    Text *text2 = new Text("Hello from NOMU Engine", fontPath, ResourceManager::GetShader("text"), 24, this->Width, this->Height, entity2->GetComponent<Transform>());
    entity2->AddComponent(text2);

    world->Init();
    
    entity->GetComponent<Transform>()->SetPosition(glm::vec2(400.0f, 400.0f));
    entity->GetComponent<Transform>()->SetScale(glm::vec2(400.0f, 400.0f));

    entity1->GetComponent<Transform>()->SetPosition(glm::vec2(300, 100));
    entity1->GetComponent<Transform>()->SetScale(glm::vec2(2, 1.0));

    entity2->GetComponent<Transform>()->SetPosition(glm::vec2(450, 770));
    entity2->GetComponent<Transform>()->SetScale(glm::vec2(1.0, 1.0));
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
    if(entity->GetComponent<EventListener>()->isLeftClicked()){
        std::cout << "Left Clicked" << std::endl;
    }
    if(entity->GetComponent<EventListener>()->isRightClicked()){
        std::cout << "Right Clicked" << std::endl;
    }

    if(entity->GetComponent<EventListener>()->isLeftClickedandHeld()){
        entity->GetComponent<Transform>()->SetPosition(*MousePos);
    }
}