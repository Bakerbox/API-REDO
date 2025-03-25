#pragma once
#include "Entity.h"
#include "vector"
class Background {
private:
    std::vector<Vector2> stars;
    int starCount;
    float speed;

public:
    explicit Background(int count);
    
    ~Background() = default;
    
    void Update(float offset);
    void Render() const;
};
