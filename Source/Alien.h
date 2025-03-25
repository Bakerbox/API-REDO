#pragma once
#include "Entity.h"

class Alien : public Entity {
private:
    float speed;
    float moveTimer;
    float moveInterval;
    int moveDirection;

public:
    explicit Alien(Vector2 pos);
    
    ~Alien() override = default;
    
    void Update() override;
    void Render(const Texture2D& texture) const override;
    
    bool CollideWith(const Entity& other) const override;
    bool CollideWith(const Player& player) const override;
    bool CollideWith(const Alien& alien) const override;
    bool CollideWith(const Projectile& projectile) const override;
    bool CollideWith(const Wall& wall) const override;
};
