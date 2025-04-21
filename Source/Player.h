#pragma once
#include "Entity.h"
#include "Resources.h"
#include "Alien.h"
#include "Projectile.h"
#include "Wall.h"
class Player : public Entity {
private:
    int lives;
    float speed;
    float frameTimer;
    int textureFrame;
    float playerBaseHeight;

public:
    Player();
    
    ~Player() override = default;
    
    void Update() override;
    void Render(const Texture2D& texture) const override;
    
    void Render(const Resources& resources) const noexcept;
    
    int GetLives() const noexcept { return lives; }
    float GetPlayerBaseHeight() const noexcept { return playerBaseHeight; }
    int GetTextureFrame() const noexcept { return textureFrame; }
    
    void DecreaseLife() noexcept;
    
    bool CollideWith(const Entity& other) const override;
    bool CollideWith(const Player& player) const override;
    bool CollideWith(const Alien& alien) const override;
    bool CollideWith(const Projectile& projectile) const override;
    bool CollideWith(const Wall& wall) const override;
};
