#pragma once
#include <raylib.h>
#include <string>
#include <memory>
#include <stdexcept>

class TextureResource {
private:
    Texture2D texture;

public:
    explicit TextureResource(const std::string& path) {
        texture = LoadTexture(path.c_str());
        if (texture.id == 0) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
    }

    ~TextureResource() {
        if (texture.id != 0) {
            UnloadTexture(texture);
        }
    }

    // Rule of 5: Delete copy operations, implement move operations
    TextureResource(const TextureResource&) = delete;
    TextureResource& operator=(const TextureResource&) = delete;

    TextureResource(TextureResource&& other) noexcept : texture(other.texture) {
        other.texture.id = 0;
    }
    
    TextureResource& operator=(TextureResource&& other) noexcept {
        if (this != &other) {
            if (texture.id != 0) {
                UnloadTexture(texture);
            }
            texture = other.texture;
            other.texture.id = 0;
        }
        return *this;
    }

    const Texture2D& get() const noexcept {
        return texture;
    }
    
    Texture2D& get() noexcept {
        return texture;
    }
};
