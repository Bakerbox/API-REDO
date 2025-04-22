#pragma once
#include "raylib.h"
#include <string>

struct PlayerData {
    std::string name;
    int score;
};

class  Highscore
{
private:


public:




std::vector<PlayerData> leaderboard;
bool mouseOnText = false;
int score = 0;
bool newHighScore = false;
std::string playerName;
int framesCounter = 0;
Rectangle textBox = { 600, 500, 225, 50 };

void RenderTextBoxOutline() const {
    const auto outlineColor = mouseOnText ? RED : DARKGRAY;
    DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y),
        static_cast<int>(textBox.width), static_cast<int>(textBox.height), outlineColor);
}

void RenderBlinkingCursor() const {


    if ((framesCounter / 20) % 2 == 0) {
        const int cursorX = static_cast<int>(textBox.x) + 8 + MeasureText(playerName.c_str(), 40);
        const int cursorY = static_cast<int>(textBox.y) + 12;
        DrawText("_", cursorX, cursorY, 40, MAROON);
    }
}

void RenderNewHighScoreScreen() const {
    constexpr int textX = 600;
    DrawText("NEW HIGHSCORE!", textX, 300, 60, YELLOW);
    DrawText("PLACE MOUSE OVER INPUT BOX!", textX, 400, 20, YELLOW);

    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawText(playerName.c_str(), static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);
    DrawText("INPUT CHARS: ", textX, 600, 20, YELLOW);

    RenderTextBoxOutline();
    RenderBlinkingCursor();

    if (playerName.size() > 0) {
        DrawText("PRESS ENTER TO CONTINUE", textX, 800, 40, YELLOW);
    }
}





void RenderLeaderboardScreen() const {
    DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
    DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

    int yOffset = 140;
    const int nameX = 50;
    const int scoreX = 350;
    const int rowHeight = 40;

    for (const auto& entry : leaderboard) {
        DrawText(entry.name.c_str(), nameX, yOffset, 40, YELLOW);
        DrawText(TextFormat("%i", entry.score), scoreX, yOffset, 40, YELLOW);
        yOffset += rowHeight;
    }
}

void InsertNewHighScore(const std::string& name) {
    PlayerData newData{ name, score };

    leaderboard.push_back(newData);
    std::sort(leaderboard.begin(), leaderboard.end(), [](const PlayerData& a, const PlayerData& b) {
        return a.score > b.score;
        });

    if (leaderboard.size() > 5) {
        leaderboard.pop_back();
    }
}


bool CheckNewHighScore()  {
    if (leaderboard.empty()) return true;

    return score > leaderboard.back().score;
}

void HandleNameInput() {
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125)) {
            playerName.push_back(static_cast<char>(key));
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !playerName.empty()) {
        playerName.pop_back();
    }
}

void HandleHighScoreEntry() {
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
        mouseOnText = true;
    }
    else {
        mouseOnText = false;
    }

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        HandleNameInput();
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (mouseOnText) {
        framesCounter++;
    }
    else {
        framesCounter = 0;
    }

    if (playerName.size() > 0 && IsKeyReleased(KEY_ENTER)) {
        InsertNewHighScore(playerName);
        newHighScore = false;
    }
}

};