#include <array>

#include <raylib.h>
#include <raymath.h>

struct Circle
{
    Vector2 position;
    float radius;
};

int main()
{
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;
    const unsigned int targetFPS = 60;

    InitWindow(windowWidth, windowHeight, "raylib Template");
    SetTargetFPS(targetFPS);

    const unsigned int numCircles = 10;
    std::array<Circle, numCircles> circles;

    for (unsigned int i = 0; i < numCircles; i++)
    {
        Circle circle;
        circle.radius = static_cast<float>(GetRandomValue(25, 100));
        circle.position = {
            static_cast<float>(GetRandomValue(circle.radius, windowWidth - circle.radius)),
            static_cast<float>(GetRandomValue(circle.radius, windowHeight - circle.radius))};

        circles[i] = circle;
    }

    while (!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto &circle : circles)
        {
            DrawCircleLines(circle.position.x, circle.position.y, circle.radius, GRAY);
        }

        EndDrawing();
    }

    return 0;
}