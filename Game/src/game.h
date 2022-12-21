#pragma once
#include <core/app.h>
#include <core/game.h>
#include <ecs/entity.h>
#include <components/transform.h>
#include <components/ui_sprite.h>
#include <components/event_listener.h>

#include <renderer/ui_sprite_renderer.h>
#include <utils/resource_manager.h>
#include <renderer/text_renderer.h>

class MyGame : public Nomu::Game
{
public:
    // game state
    bool                    wireframe;
    Nomu::Entity*                 root;
    // constructor/destructor
    MyGame();
    ~MyGame();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void SetApp(Nomu::App& app);
private:
    Nomu::App* mApp;
};
