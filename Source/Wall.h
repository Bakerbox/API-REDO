#pragma once
#include "Entity.h"

class Wall : public Entity {
private:
    int health;
    
public:
    // Constructor with proper initialization
    explicit Wall(Vector2 pos);
    
    // Rule of 0: Let compiler generate destructor, copy/move operations
    ~Wall() override = default;
    
    // Override pure virtual functions from Entity
    void Update() override;
    void Render(const Texture2D& texture) const override;
    
    // Game mechanics
    void TakeDamage() noexcept;
    
    // Collision visitor pattern implementation
    bool CollideWith(const Entity& other) const override;
    bool CollideWith(const Player& player) const override;
    bool CollideWith(const Alien& alien) const override;
    bool CollideWith(const Projectile& projectile) const override;
    bool CollideWith(const Wall& wall) const override;
};
