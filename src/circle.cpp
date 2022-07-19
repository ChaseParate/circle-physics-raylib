#include <raylib.h>
#include <raymath.h>

#include "circle.hpp"

bool Circle::collidePoint(Vector2 point)
{
    float distance = Vector2Distance(position, point);
    return distance <= radius;
}

bool Circle::collideCircle(Circle &other)
{
    float distance = Vector2Distance(position, other.position);
    return distance <= radius + other.radius;
}

void Circle::resolveStaticCollision(Circle &other)
{
    if (id == other.id || !collideCircle(other))
        return;

    float distance = Vector2Distance(position, other.position);
    float overlap = (distance - radius - other.radius) / 2;
    // std::printf("IDs: %d, %d\tRadii: %.1f, %.1f\tDistance: %.2f \tOverlap: %.2f\n",
    //             id, other.id, radius, other.radius, distance, overlap);

    Vector2 deltaPosition = Vector2Subtract(position, other.position);
    Vector2 moveAmount = Vector2Scale(deltaPosition, overlap / distance);

    position = Vector2Subtract(position, moveAmount);
    other.position = Vector2Add(other.position, moveAmount);
}

void Circle::draw()
{
    DrawCircleLines(position.x, position.y, radius, GRAY);

    unsigned int fontSize = radius;
    const char *text = TextFormat("%d", id);
    unsigned int textWidth = MeasureText(text, fontSize);

    DrawText(text, position.x - (textWidth / 2), position.y - (fontSize / 2), fontSize, GRAY);
}