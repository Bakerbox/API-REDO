#include "Resources.h"
#include <stdexcept>

Resources::Resources() : alienTexture("./Assets/Alien.png"),
barrierTexture("./Assets/Barrier.png"),
laserTexture("./Assets/Laser.png")
{
    try {
       
        
        shipTextures.reserve(3);
        shipTextures.emplace_back(TextureResource("./Assets/Ship1.png"));
        shipTextures.emplace_back(TextureResource("./Assets/Ship2.png"));
        shipTextures.emplace_back(TextureResource("./Assets/Ship3.png"));
    }
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Failed to initialize resources: ") + e.what());
    }
}

const Texture2D& Resources::GetPlayerTexture(size_t index) const {
    if (index >= shipTextures.size()) {
        throw std::out_of_range("Ship texture index out of range");
    }
    return shipTextures[index].get();
}
