#include "Alien.h"
#include "Player.h"
#include "Projectile.h"
#include "Wall.h"
#include <raylib.h>
#include <random>

Alien::Alien(Vector2 pos)
    : Entity(pos, 65, 40),
      speed(5.0f),
      moveTimer(0.0f),
      moveInterval(1.0f),
      moveDirection(1)
{
}

void Alien::Update() {
    if (!IsActive()) return;
    
    moveTimer += 1.0f;
    
    if (moveTimer >= moveInterval) {
        position.x += speed * moveDirection;
        
        if (position.x < width || position.x > GetScreenWidth() - width) {
            moveDirection *= -1;
            position.y += 10.0f;
        }
        
        moveTimer = 0.0f;
    }
}

void Alien::Render(const Texture2D& texture) const {
    if (!IsActive()) return;
    
    DrawTexturePro(texture,
        {
            0,
            0,
            352,
            352,
        },
        {
            position.x,
            position.y,
            100,
            100,
        }, { 50 , 50 },
        0,
        WHITE);
}

bool Alien::CollideWith(const Entity& other) const {
    return other.CollideWith(*this);
}

bool Alien::CollideWith(const Player& player) const {
    return IsColliding(player);
}

bool Alien::CollideWith(const Alien& alien) const {
    return false;
}

bool Alien::CollideWith(const Projectile& projectile) const {
    return projectile.IsPlayerProjectile() && IsColliding(projectile);
}

bool Alien::CollideWith(const Wall& wall) const {
    return IsColliding(wall);
}
