#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ecs/world.h"
#include "components/transform.h"
#include "components/sprite.h"

#include "renderer/sprite_renderer.h"
#include "utils/resource_manager.h"
#include "renderer/text_renderer.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;	
    bool                    Keys[1024];
    unsigned int            Width, Height;
    double                  MouseX, MouseY;
    bool                    MouseLeft, MouseRight;
    bool                    wireframe;
    World                   *world;
    Entity                  *entity;
    Sprite                  *sprite;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};

#endif
