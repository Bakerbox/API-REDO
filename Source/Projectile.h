#pragma once
#include "Entity.h"

class Projectile : public Entity {
private:
    int speed;
    bool isPlayerProjectile;

public:
    Projectile(Vector2 pos, bool isPlayer);
    
    ~Projectile() override = default;
    
    void Update() override;
    void Render(const Texture2D& texture) const override;
    
    bool IsPlayerProjectile() const noexcept { return isPlayerProjectile; }
    
    void InverseSpeed() noexcept { speed = -speed; }
    void OffsetEnemyProjectile() noexcept;
    
    bool CollideWith(const Entity& other) const override;
    bool CollideWith(const Player& player) const override;
    bool CollideWith(const Alien& alien) const override;
    bool CollideWith(const Projectile& projectile) const override;
    bool CollideWith(const Wall& wall) const override;
};
