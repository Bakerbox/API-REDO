#pragma once
#include <vector>
#include <string>
#include <random>
#include <memory>
#include "Resources.h"
#include "Player.h"
#include "Wall.h"
#include "Alien.h"
#include "Projectile.h"
#include "Background.h"

//TODO: fix the physical structure. Move things into their own files. 
// higschore, collision code, rng, etc. (pytting implementation in .hpp files is fine). 
// Forward declarations
class Background;

enum class State {
    STARTSCREEN,
    GAMEPLAY,
    ENDSCREEN
};

struct PlayerData {
    std::string name;
    int score;
};

class Game {
private:
    // Game state
    State gameState;
    int score;
    bool newHighScore;
    std::string playerName;
    int letterCount;
    int framesCounter;
    
    // Game configuration
    // TODO: consider making static constexpr and inline-initialize (and maybe make public / put in a config-namespace)
    int wallCount;
    float shootTimer;
    float shootInterval;
    int formationWidth;
    int formationHeight;
    int alienSpacing;
    int formationX;
    int formationY;
    
    std::mt19937 rng;
    
    std::unique_ptr<Player> player;
    Background background;
    std::vector<Projectile> projectiles;
    std::vector<Wall> walls;
    std::vector<Alien> aliens;
    std::vector<PlayerData> leaderboard;
    
    bool mouseOnText;
    Vector2 cornerPos;
    float offset;
    Rectangle textBox;
    
    std::unique_ptr<Resources> resources;
    
    void HandleGameplay();
    void HandlePlayerInput();
    void UpdateEntities();
    void HandleCollisions();
    void HandleProjectileCollisions(Projectile& projectile);
    void SpawnNewAliensIfNecessary();
    void UpdateBackground();
    void HandleShooting();
    void SpawnEnemyProjectile();
    void SpawnPlayerProjectile();
    void CleanupInactiveEntities();
    void ShowEndScreen();
    void HandleHighScoreEntry();
    void HandleNameInput();
    void RenderNewHighScoreScreen() const;
    void RenderTextBoxOutline() const;
    void RenderBlinkingCursor() const;
    void RenderLeaderboardScreen() const;
    bool CheckNewHighScore() const;
    void InsertNewHighScore(const std::string& name);

public:
    explicit Game(State initialState);
    
    ~Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(Game&&) = default;
    Game& operator=(Game&&) = default;
    
    
    void Reset();
    void Update();
    void Render() const;
    void End();
    
    
    void ShowStartScreen();
    void SpawnAliens();
};
