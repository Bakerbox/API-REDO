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
#include "Highscore.h"
class Background;

enum class State {
    STARTSCREEN,
    GAMEPLAY,
    ENDSCREEN
};



class Game {
private:
    // Game state
    State gameState;

    
    // Game configuration
    float shootTimer = 0;
    static constexpr int wallCount = 5;
    static constexpr float shootInterval = 60.0f;
    static constexpr int formationWidth = 8;
    static constexpr int formationHeight = 5;
    static constexpr int alienSpacing = 80;
    static constexpr int formationX = 100;
    static constexpr int formationY = 50;
    std::mt19937 rng;
    
    std::unique_ptr<Player> player;
    Background background;
    std::vector<Projectile> projectiles;
    std::vector<Wall> walls;
    std::vector<Alien> aliens;

    

    Vector2 cornerPos = { 0, 0 };
    float offset = 0;

    
    Resources resources;
    Highscore highscore;
    
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
