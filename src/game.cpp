#include "game.h"

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
    delete Renderer;
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
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
#ifndef linux
    ResourceManager::LoadTexture("F:/C++/NomuEngine/src/textures/nomu.png", true, "face");
    std::cout << "Loaded texture: " << "F:/C++/NomuEngine/src/textures/nomu.png" << std::endl;
#else
    ResourceManager::LoadTexture("/mnt/f/C++/NomuEngine/src/textures/nomu.png", true, "face");
    std::cout << "Loaded texture: " << "/mnt/f/C++/src/textures/nomu.png" << std::endl;
#endif
    Text = new TextRenderer(this->Width, this->Height);
#ifndef linux
    Text->Load("F:/C++/NomuEngine/src/fonts/OCRAEXT.ttf", 24);
#else
    Text->Load("/mnt/f/C++/NomuEngine/src/fonts/OCRAEXT.ttf", 24);
#endif
}

void Game::Update(float dt)
{
    
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

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"),
                         glm::vec2(MouseX, MouseY), glm::vec2(400.0f, 400.0f), 00.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    Text->RenderText("Hello!", 300.0f, 100.0f, 2.0f);
    Text->RenderText("From Nomu Engine", 550.0f, 770.0f, 1.0f);
}
