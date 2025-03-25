#include "Collisions.h"
#include <cmath>

// Line-circle collision detection using vector math
bool CheckCollision(Vector2 center, float radius, Vector2 lineStart, Vector2 lineEnd) {
    // Vector from line start to center
    Vector2 d1 = {
        center.x - lineStart.x,
        center.y - lineStart.y
    };
    
    // Vector representing the line
    Vector2 d2 = {
        lineEnd.x - lineStart.x,
        lineEnd.y - lineStart.y
    };
    
    // Calculate the length of the line
    float lineLen = std::sqrt(d2.x * d2.x + d2.y * d2.y);
    
    // Normalize the line vector
    if (lineLen > 0) {
        d2.x /= lineLen;
        d2.y /= lineLen;
    }
    
    // Calculate the projection of d1 onto d2
    float t = d1.x * d2.x + d1.y * d2.y;
    
    // Find the closest point on the line to the circle center
    Vector2 closestPoint;
    
    // Clamp t to the line segment
    t = std::max(0.0f, std::min(t, lineLen));
    
    closestPoint.x = lineStart.x + t * d2.x;
    closestPoint.y = lineStart.y + t * d2.y;
    
    // Calculate the distance from the closest point to the circle center
    float distance = std::sqrt(
        (center.x - closestPoint.x) * (center.x - closestPoint.x) +
        (center.y - closestPoint.y) * (center.y - closestPoint.y)
    );
    
    // Check if the distance is less than or equal to the radius
    return distance <= radius;
}

// Calculate length between two points
float lineLength(Vector2 start, Vector2 end) {
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    return std::sqrt(dx * dx + dy * dy);
}
