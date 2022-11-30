#include <core/engine.h>
#include <core/app.h>

#include "game.h"

int main(){
    Nomu::App app {
        nullptr,
        "Nomu Engine",
        800,
        800,
        0,
        0,
        {false},
        false,
        false,
        {0.0f, 0.0f},
        0.0f,
        0.0f
    };

    Nomu::Engine engine(&app);

    MyGame game;
    game.SetApp(app);
    engine.setGame(&game);
    engine.Init();
    engine.Run();
    return 0;
}



