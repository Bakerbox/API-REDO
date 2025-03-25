#include "Background.h"
#include <raylib.h>
#include <random>
#include <chrono>

Background::Background(int count)
    : starCount(count),
      speed(1.0f)
{
    // Seed random number generator
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> distX(0, GetScreenWidth());
    std::uniform_int_distribution<int> distY(0, GetScreenHeight());
    
    // Reserve space for stars to avoid reallocations
    stars.reserve(starCount);
    
    // Create stars with random positions
    for (int i = 0; i < starCount; ++i) {
        stars.push_back({
            static_cast<float>(distX(rng)),
            static_cast<float>(distY(rng))
        });
    }
}

void Background::Update(float offset) {
    // Move stars based on offset
    for (auto& star : stars) {
        star.y += speed + offset;
        
        // Wrap stars around screen
        if (star.y > GetScreenHeight()) {
            star.y = 0;
        } else if (star.y < 0) {
            star.y = static_cast<float>(GetScreenHeight());
        }
    }
}

void Background::Render() const {
    // Draw stars
    for (const auto& star : stars) {
        DrawPixel(static_cast<int>(star.x), static_cast<int>(star.y), WHITE);
    }
}
