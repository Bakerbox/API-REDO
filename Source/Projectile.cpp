#include "Projectile.h"
#include "Player.h"
#include "Alien.h"
#include "Wall.h"
#include <raylib.h>

constexpr int PROJECTILE_SPEED = 15;
constexpr float ALIEN_OFFSET = 40.0f;

Projectile::Projectile(Vector2 pos, bool isPlayer)
    : Entity(pos, 0.0f),
      speed(isPlayer ? PROJECTILE_SPEED : -PROJECTILE_SPEED),
      lineStart({0, 0}),
      lineEnd({0, 0}),
      isPlayerProjectile(isPlayer)
{
}

void Projectile::Update() {
    position.y -= speed;
    
    lineStart = position;
    lineEnd = {position.x, position.y - 10.0f};
    
    if (position.y < 0 || position.y > GetScreenHeight()) {
        SetActive(false);
    }
}

void Projectile::Render(const Texture2D& texture) const {
    if (!IsActive()) return;
    
    DrawTexturePro(texture,
        {
            0,
            0,
            176,
            176,
        },
        {
            position.x,
            position.y,
            50,
            50,
        }, { 25 , 25 },
        0,
        WHITE);
}

void Projectile::OffsetEnemyProjectile() noexcept {
    if (!isPlayerProjectile) {
        position.y += ALIEN_OFFSET;
    }
}

bool Projectile::CollideWith(const Entity& other) const {
    return other.CollideWith(*this);
}

bool Projectile::CollideWith(const Player& player) const {
    return !isPlayerProjectile && IsColliding(player);
}

bool Projectile::CollideWith(const Alien& alien) const {
    return isPlayerProjectile && IsColliding(alien);
}

bool Projectile::CollideWith(const Projectile& projectile) const {
    return false;
}

bool Projectile::CollideWith(const Wall& wall) const {
    return IsColliding(wall);
}
