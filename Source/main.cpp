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
            
            BeginDrawing(); //TODO: considermoving into game::render, since it 100% dependent on these calls happening in the right order
            ClearBackground(BLACK);
            game.Render();
            EndDrawing();
        }
        
        CloseWindow();
        
    }
    catch (const std::exception& e) {
        // Handle any exceptions that might be thrown
        TraceLog(LOG_ERROR, "Exception caught: %s", e.what());
        //TODO: consider using std::cerr for exceptional / error outputs, but tracelog probably does something similar
        CloseWindow();        
    }
    return EXIT_SUCCESS;
}
