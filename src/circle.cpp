#include <raylib.h>
#include <raymath.h>

#include "circle.hpp"

void Circle::resolveStaticCollision(Circle &other)
{
    float distance = Vector2Distance(position, other.position);
    float overlap = (distance - radius - other.radius) / 2;

    Vector2 deltaPosition = Vector2Subtract(position, other.position);
    Vector2 moveAmount = Vector2Scale(deltaPosition, overlap / distance);

    position = Vector2Subtract(position, moveAmount);
    other.position = Vector2Add(other.position, moveAmount);
}

void Circle::resolveDynamicCollision(Circle &other)
{
    float mass = radius * 10.0f;
    float otherMass = other.radius * 10.0f;

    Vector2 deltaPosition = Vector2Subtract(position, other.position);
    Vector2 normal = Vector2Normalize(deltaPosition);

    Vector2 deltaVelocity = Vector2Subtract(velocity, other.velocity);
    float momentum = 2.0f * Vector2DotProduct(normal, deltaVelocity) / (mass + otherMass);

    velocity = Vector2Subtract(velocity, Vector2Scale(normal, momentum * otherMass));
    other.velocity = Vector2Add(other.velocity, Vector2Scale(normal, momentum * mass));
}

void Circle::draw()
{
    DrawCircleLines(position.x, position.y, radius, GRAY);
    DrawLineV(position, Vector2Add(position, Vector2Scale(Vector2Normalize(velocity), radius)), GRAY);

    unsigned int fontSize = radius;
    const char *text = TextFormat("%d", id);
    unsigned int textWidth = MeasureText(text, fontSize);

    DrawText(text, position.x - (textWidth / 2), position.y - (fontSize / 2), fontSize, GRAY);
}