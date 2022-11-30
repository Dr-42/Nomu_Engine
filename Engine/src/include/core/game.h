#pragma once
namespace Nomu
{
    class N_API Game
    {
    public:
        Game() = default;
        ~Game() = default;
        // initialize game state (load all shaders/textures/levels)
        virtual void Init() = 0;
        // game loop
        virtual void ProcessInput(float dt) = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
    };
}