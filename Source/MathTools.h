#pragma once
#include <cmath>
#include <raylib.h>

 inline float lineLength(Vector2 start, Vector2 end) {
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    return std::sqrt(dx * dx + dy * dy);
}
