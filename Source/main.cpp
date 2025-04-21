#include "Window.h"
#include "game.h"
constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

int main()
{
    try {
       WindowRAII(screenWidth, screenHeight, "SPACE INVADERS");
        
        Game game(State::STARTSCREEN);

        while (!WindowShouldClose())
        {
            game.Update();
            game.Render();

        }
        
    }
    catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "Exception caught: %s", e.what());   
    }
    return EXIT_SUCCESS;
}
