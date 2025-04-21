#pragma once
#include <raylib.h>
#include <memory>

class Player;
class Alien;
class Projectile;
class Wall;

class Entity {
protected:
    Vector2 position;
    float width;
    float height;
    bool active = true;

public:
    Rectangle GetBounds(const Entity& entity) const {
        return  Rectangle{ entity.position.x-entity.width/2, entity.position.y, entity.width, entity.height };
    }
    Entity() : width(0),height(0), position{0, 0} {}
    Entity(Vector2 pos, float w, float h) : position(pos), width(w), height(h) {}
    
    virtual ~Entity() = default;

    virtual void Update() = 0;
    virtual void Render(const Texture2D& texture) const = 0;

    Vector2 GetPosition() const { return position; }
    float GetXPosition() const { return position.x; }
    float GetYPosition() const { return position.y; }
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    bool IsActive() const { return active; }
    void SetActive(bool isActive) { active = isActive; }
    void SetPosition(Vector2 newPos) { position = newPos; }

    //TODO: rect-rect is probably more suited for this game. (projectiles, walls - most things are more rectangular than circular)
    bool IsColliding(const Entity& other) const {
        return CheckCollisionRecs(GetBounds(*this), GetBounds(other));
    }
    
    virtual bool CollideWith(const Entity& other) const = 0;
    virtual bool CollideWith(const Player& player) const = 0;
    virtual bool CollideWith(const Alien& alien) const = 0;
    virtual bool CollideWith(const Projectile& projectile) const = 0;
    virtual bool CollideWith(const Wall& wall) const = 0;
};
