#pragma once
#include <vector>
#include <memory>
#include <string>
#include "TextureResource.h"

class Resources {
private:
    //TODO: you don't need a pointer. Just own the TextureResource
    TextureResource alienTexture;
    TextureResource barrierTexture;
    TextureResource laserTexture;
    std::vector<TextureResource> shipTextures;

public:
    Resources();
    
    ~Resources() = default;
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;
    Resources(Resources&&) = default;
    Resources& operator=(Resources&&) = default;

    const Texture2D& GetAlienTexture() const noexcept { return alienTexture.get(); }
    const Texture2D& GetBarrierTexture() const noexcept { return barrierTexture.get(); }
    const Texture2D& GetLaserTexture() const noexcept { return laserTexture.get(); }
    
    const Texture2D& GetPlayerTexture(size_t index) const;
    
    size_t GetShipTextureCount() const noexcept { return shipTextures.size(); }
};
