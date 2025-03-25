#include "Wall.h"
#include "Player.h"
#include "Alien.h"
#include "Projectile.h"
#include <raylib.h>

constexpr int INITIAL_WALL_HEALTH = 3;

Wall::Wall(Vector2 pos)
    : Entity(pos, 40.0f),
      health(INITIAL_WALL_HEALTH)
{
}

void Wall::Update() {
    if (health <= 0) {
        SetActive(false);
    }
}

void Wall::Render(const Texture2D& texture) const {
    if (!IsActive()) return;
    
    Color wallColor = WHITE;
    switch (health) {
        case 3: wallColor = WHITE; break;
        case 2: wallColor = YELLOW; break;
        case 1: wallColor = ORANGE; break;
        default: wallColor = RED; break;
    }
    
    DrawTexturePro(texture,
        { 0, 0, 704, 704 },
        { position.x, position.y, 200, 200 },
        { 100, 100 },
        0.0f,
        WHITE);
    if (health > 0) {
        DrawText(TextFormat("%i", health), static_cast<int>(position.x) - 10, static_cast<int>(position.y) - 10, 20, RED);
    }
}

void Wall::TakeDamage() noexcept {
    if (health > 0) {
        health--;
    }
}

bool Wall::CollideWith(const Entity& other) const {
    return other.CollideWith(*this);
}

bool Wall::CollideWith(const Player& player) const {
    return false;
}

bool Wall::CollideWith(const Alien& alien) const {
    return IsColliding(alien);
}

bool Wall::CollideWith(const Projectile& projectile) const {
    return IsColliding(projectile);
}

bool Wall::CollideWith(const Wall& wall) const {
    return false;
}
