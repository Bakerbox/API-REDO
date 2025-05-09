#include "game.h"
#include "Background.h"
#include "MathTools.h"
#include <algorithm>
#include <random>
#include <chrono>

constexpr float WALL_DISTANCE = 300.0f;
constexpr float ALIEN_DISTANCE = 450.0f;
constexpr float PROJECTILE_DISTANCE = 130.0f;
constexpr float SHOOT_INTERVAL = 60.0f;
constexpr int MAX_NAME_LENGTH = 8;
constexpr int LEADERBOARD_ROWS = 5;

Game::Game(State initialState)
    : gameState(initialState),
      background(600)
{
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    rng.seed(seed);
    
    player = std::make_unique<Player>();
    
    highscore.leaderboard = {
        {"Player 1", 500},
        {"Player 2", 400},
        {"Player 3", 300},
        {"Player 4", 200},
        {"Player 5", 100}
    };
    
    Reset();
}

void Game::End() {
    projectiles.clear();
    walls.clear();
    aliens.clear();
    highscore.newHighScore = highscore.CheckNewHighScore();
    gameState = State::ENDSCREEN;
}

void Game::Reset() {
    projectiles.clear();
    walls.clear();
    aliens.clear();
    player = std::make_unique<Player>();
    highscore.score = 0;

    const float wallY = static_cast<float>(GetScreenHeight()) - WALL_DISTANCE;
    const float wallSpacing = static_cast<float>(GetScreenWidth()) / (wallCount + 1);

    walls.reserve(wallCount);
    for (int i = 0; i < wallCount; ++i) {
        walls.emplace_back(Vector2{wallSpacing * (i + 1), wallY});
    }
    
    SpawnAliens();
}

void Game::Update() {
    switch (gameState) {
    case State::STARTSCREEN:
        ShowStartScreen();
        break;

    case State::GAMEPLAY:
        HandleGameplay();
        break;

    case State::ENDSCREEN:
        ShowEndScreen();
        break;
    }
}

void Game::ShowStartScreen() {
    if (IsKeyReleased(KEY_SPACE)) {
        gameState = State::GAMEPLAY;
    }
}

void Game::HandleGameplay() {
    HandlePlayerInput();
    UpdateEntities();
    HandleCollisions();
    SpawnNewAliensIfNecessary();
    UpdateBackground();
    HandleShooting();
}

void Game::HandlePlayerInput() {
    if (IsKeyReleased(KEY_Q)) {
        End();
    }
}

void Game::UpdateEntities() {
    player->Update();
    if (player->GetLives() < 1) {
        End();
    }

    for (auto& alien : aliens) {
        alien.Update();
        if (alien.GetYPosition() > GetScreenHeight() - player->GetPlayerBaseHeight()) {
            End();
        }
    }

    for (auto& projectile : projectiles) {
        projectile.Update();
    }

    for (auto& wall : walls) {
        wall.Update();
    }
}

void Game::HandleCollisions() {
    for (auto& projectile : projectiles) {
        if (projectile.IsActive()) {
            HandleProjectileCollisions(projectile);
        }
    }
}

void Game::HandleProjectileCollisions(Projectile& projectile) {
    if (projectile.IsPlayerProjectile()) {
        for (auto& alien : aliens) {
            if (alien.IsActive() && projectile.CollideWith(alien)) {
                projectile.SetActive(false);
                alien.SetActive(false);
                highscore.score += 100;
            }
        }
    } else {
        if (projectile.CollideWith(*player)) {
            projectile.SetActive(false);
            player->DecreaseLife();
        }
    }
    
    for (auto& wall : walls) {
        if (wall.IsActive() && projectile.CollideWith(wall)) {
            projectile.SetActive(false);
            wall.TakeDamage();
        }
    }
}

void Game::SpawnNewAliensIfNecessary() {
    if (aliens.empty()) {
        SpawnAliens();
    }
}

void Game::UpdateBackground() {
    cornerPos = {0, player->GetPlayerBaseHeight()};
    offset = lineLength(player->GetPosition(), cornerPos) * -1;
    background.Update(offset / 15);
}

void Game::HandleShooting() {
    shootTimer += 1;
    if (shootTimer > shootInterval - 1) {
        SpawnEnemyProjectile();
        shootTimer = 0;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        SpawnPlayerProjectile();
    }

    CleanupInactiveEntities();
}

void Game::SpawnPlayerProjectile() {
    Vector2 projectilePos = {
        player->GetXPosition(),
        static_cast<float>(GetScreenHeight()) - PROJECTILE_DISTANCE
    };
    projectiles.emplace_back(projectilePos, true);
}

void Game::CleanupInactiveEntities() {
    std::erase_if(projectiles, [](const Projectile& projectile) { 
        return !projectile.IsActive(); 
    });
    
    std::erase_if(aliens, [](const Alien& alien) { 
        return !alien.IsActive(); 
    });
    
    std::erase_if(walls, [](const Wall& wall) { 
        return !wall.IsActive(); 
    });
}

void Game::ShowEndScreen() {
    if (IsKeyReleased(KEY_ENTER) && !highscore.newHighScore) {
        Reset();
        gameState = State::STARTSCREEN;
    }

    if (highscore.newHighScore) {
        highscore.HandleHighScoreEntry();
    }
}



void Game::SpawnEnemyProjectile() {
    if (aliens.empty()) return;

    std::uniform_int_distribution<size_t> dist(0, aliens.size() - 1);
    size_t randomAlienIndex = dist(rng);

    if (randomAlienIndex < aliens.size()) {
        Vector2 projectilePos = aliens[randomAlienIndex].GetPosition();
        Projectile newProjectile(projectilePos, false);
        newProjectile.OffsetEnemyProjectile();
        projectiles.push_back(std::move(newProjectile)); //if you move, you could use emplace_back to trigger the move-constructor in place. I think this will happen implicitly, but it's nice being explicit.
    }
}



void Game::Render() const {
    BeginDrawing();
    ClearBackground(BLACK);
    switch (gameState) {
    case State::STARTSCREEN:
        DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
        DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
        break;

    case State::GAMEPLAY:
        background.Render();
        DrawText(TextFormat("Score: %i", highscore.score), 50, 20, 40, YELLOW);
        DrawText(TextFormat("Lives: %i", player->GetLives()), 50, 70, 40, YELLOW);

        player->Render(resources);
        
        for (const auto& projectile : projectiles) {
            if (projectile.IsActive()) {
                projectile.Render(resources.GetLaserTexture());
            }
        }
        
        for (const auto& wall : walls) {
            if (wall.IsActive()) {
                wall.Render(resources.GetBarrierTexture());
            }
        }
        
        for (const auto& alien : aliens) {
            if (alien.IsActive()) {
                alien.Render(resources.GetAlienTexture());
            }
        }
        break;

    case State::ENDSCREEN:
        if (highscore.newHighScore) {
            highscore.RenderNewHighScoreScreen();
        } else {
            highscore.RenderLeaderboardScreen();
        }
        break;
    }
    EndDrawing();
}

void Game::SpawnAliens() {
    aliens.reserve(formationWidth * formationHeight);
    
    for (int row = 0; row < formationHeight; ++row) {
        for (int col = 0; col < formationWidth; ++col) {
            const float xPos = static_cast<float>(formationX + col * alienSpacing);
            const float yPos = static_cast<float>(formationY + row * alienSpacing);
            aliens.emplace_back(Vector2{xPos, yPos});
        }
    }
}

