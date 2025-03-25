#include "game.h"

constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

int main()
{
    try {
        InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
        SetTargetFPS(60);
        
        Game game(State::STARTSCREEN);

        while (!WindowShouldClose())
        {
            game.Update();
            
            BeginDrawing();
            ClearBackground(BLACK);
            game.Render();
            EndDrawing();
        }
        
        CloseWindow();
        return 0;
    }
    catch (const std::exception& e) {
        // Handle any exceptions that might be thrown
        TraceLog(LOG_ERROR, "Exception caught: %s", e.what());
        CloseWindow();
        return 1;
    }
}
