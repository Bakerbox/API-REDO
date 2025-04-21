#pragma once
#include <raylib.h>

class WindowRAII {
public:
    WindowRAII(int width, int height, const char* title) {
        InitWindow(width, height, title);
        SetTargetFPS(60);
    }

    
    WindowRAII(const WindowRAII&) = delete;
    WindowRAII& operator=(const WindowRAII&) = delete;

  
    WindowRAII(WindowRAII&&) = default;
    WindowRAII& operator=(WindowRAII&&) = default;

    ~WindowRAII() {
        if (!WindowShouldClose()) {
            CloseWindow();
        }
    }
};