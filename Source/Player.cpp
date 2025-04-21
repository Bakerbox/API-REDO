#include "Player.h"
#include <raylib.h>

Player::Player()
    : Entity({static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) - 50.0f}, 50.0f),
      lives(3),
      speed(7.0f),
      frameTimer(0.0f),
      textureFrame(0),
      playerBaseHeight(70.0f)
{
}

void Player::Update() {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        position.x -= speed;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        position.x += speed;
    }

    position.x = std::max(size, std::min(position.x, static_cast<float>(GetScreenWidth()) - size));

    frameTimer += 1.0f;
    if (frameTimer > 10.0f) {
        textureFrame = (textureFrame + 1) % 3; 
        frameTimer = 0.0f;
    }
}

void Player::Render(const Texture2D& texture) const {
    const float height = static_cast<float>(GetScreenHeight());
    DrawTexturePro(texture, //TODO: consider scaling the images instead, and use DrawTexture (a much simpler interface for putting images to screen)
        { textureFrame * 352.0f, 0, 352, 352 },    
        { position.x, height - 50, 50, 50 }, 
        { 25, 25 },                                  
        0.0f,                                       
        WHITE);
}


void Player::Render(const Resources& resources)  const noexcept {
    try {
        const Texture2D& texture = resources.GetPlayerTexture(textureFrame);
        const float height = static_cast<float>(GetScreenHeight());
        DrawTexturePro(texture,
            { textureFrame * 352.0f, 0, 352, 352 },
            { position.x, height - 50, 50, 50 },
            { 25, 25 },
            0.0f,
            WHITE);
    }
    catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "Failed to render player: %s", e.what());
    }
    catch (...) {

        TraceLog(LOG_ERROR, "Unknown exception during Player::Render");
    }
}

void Player::DecreaseLife() noexcept {
    if (lives > 0) {
        lives--;
    }
}

bool Player::CollideWith(const Entity& other) const {
    return other.CollideWith(*this);
}

bool Player::CollideWith(const Player& player) const {
    return false;
}

bool Player::CollideWith(const Alien& alien) const {
    return IsColliding(alien);
}

bool Player::CollideWith(const Projectile& projectile) const {
    return IsColliding(projectile);
}

bool Player::CollideWith(const Wall& wall) const {
    return IsColliding(wall);
}
