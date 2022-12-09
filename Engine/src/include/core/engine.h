#pragma once
#include "defines.h"
#include "core/input.h"
#include "core/app.h"
#include "core/logger.h"
#include "core/game.h"

namespace Nomu {
    class N_API Engine{

    public:
        Engine(App* app);
        ~Engine();
        void setGame(Game* game);
        bl Init();
        bl Run();
        void Shutdown();

    private:
        f32 currentFrame;
        App* mApp;
        Game* mGame;
    };

}