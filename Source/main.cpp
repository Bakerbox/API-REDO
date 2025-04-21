#include "game.h"

constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

int main()
{
    try {
        InitWindow(screenWidth, screenHeight, "SPACE INVADERS"); //TODO: make RAII / local handle
        SetTargetFPS(60);
        
        Game game(State::STARTSCREEN);

        while (!WindowShouldClose())
        {
            game.Update();
            game.Render();

        }
        
        CloseWindow();
        
    }
    catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "Exception caught: %s", e.what());
        
        CloseWindow();        
    }
    return EXIT_SUCCESS;
}
