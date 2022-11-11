#include "game1.h"
#include "ecs/world.h"

#include <iostream>

Game::Game(unsigned int width, unsigned int height)
{
    this->Width = width;
    this->Height = height;
    this->MouseX = 0.0;
    this->MouseY = 0.0;
    this->MouseLeft = false;
    this->MouseRight = false;
    this->State = GAME_ACTIVE;
    wireframe = false;
}

Game::~Game()
{
    delete world;
}

void Game::Init(){
    // load shaders
#ifndef linux
    ResourceManager::LoadShader("F:/C++/NomuEngine/src/shaders/sprite_vert_shad.glsl", "F:/C++/NomuEngine/src/shaders/sprite_frag_shad.glsl", nullptr, "sprite");
    std::cout << "Loaded shader win" << std::endl;
#else
    ResourceManager::LoadShader("/mnt/f/C++/NomuEngine/src/shaders/sprite_vert_shad.glsl", "/mnt/f/C++/NomuEngine/src/shaders/sprite_frag_shad.glsl", nullptr, "sprite");
    std::cout << "Loaded shader lin" << std::endl;
#endif  
#ifndef linux
    ResourceManager::LoadTexture("F:/C++/NomuEngine/src/textures/nomu.png", true, "face");
    std::cout << "Loaded texture: " << "F:/C++/NomuEngine/src/textures/nomu.png" << std::endl;
#else
    ResourceManager::LoadTexture("/mnt/f/C++/NomuEngine/src/textures/nomu.png", true, "face");
    std::cout << "Loaded texture: " << "/mnt/f/C++/src/textures/nomu.png" << std::endl;
#endif

    world = new World();

    entity = world->GetEntityManager()->AddEntity("nomu");
    sprite = new Sprite(800, 800, ResourceManager::GetTexture("face"), ResourceManager::GetShader("sprite"), this->Width, this->Height, entity->GetTransform());
    entity->AddComponent(sprite);
    sprite->SetTexture(ResourceManager::GetTexture("face"));

    entity1 = world->GetEntityManager()->AddEntity("nomu2");
    Text *text = new Text("Hello", 24, this->Width, this->Height, entity1->GetTransform());
    entity1->AddComponent(text);

    entity2 = world->GetEntityManager()->AddEntity("nomu3");
    Text *text2 = new Text("Hello from NOMU Engine", 24, this->Width, this->Height, entity2->GetTransform());
    entity2->AddComponent(text2);

    world->Init();
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

    entity->GetTransform()->SetPosition(glm::vec2(MouseX, MouseY));
    entity->GetTransform()->SetScale(glm::vec2(400.0f, 400.0f));

    entity1->GetTransform()->SetPosition(glm::vec2(300, 100));
    entity1->GetTransform()->SetScale(glm::vec2(2, 1.0));

    entity2->GetTransform()->SetPosition(glm::vec2(450, 770));
    entity2->GetTransform()->SetScale(glm::vec2(1.0, 1.0));

    world->Update();
}