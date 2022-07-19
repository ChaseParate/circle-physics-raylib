#include <cstdio>
#include <vector>
#include <utility>

#include <raylib.h>
#include <raymath.h>

#include "circle.hpp"

int main()
{
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;
    const unsigned int targetFPS = 60;

    InitWindow(windowWidth, windowHeight, "raylib Template");
    SetTargetFPS(targetFPS);

    const unsigned int numCircles = 10;
    std::vector<Circle> circles;
    circles.reserve(numCircles);

    for (unsigned int i = 0; i < numCircles; i++)
    {
        float radius = GetRandomValue(25, 100);
        Vector2 position = {
            static_cast<float>(GetRandomValue(radius, windowWidth - radius)),
            static_cast<float>(GetRandomValue(radius, windowHeight - radius))};
        Circle circle = Circle(i, radius, position);

        circles.push_back(circle);
    }

    int selectedCircleID = -1;

    while (!WindowShouldClose())
    {
        // Update
        float deltaTime = GetFrameTime();
        Vector2 mousePosition = GetMousePosition();

        // Select Circle
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            selectedCircleID = -1;
            for (auto &circle : circles)
            {
                if (!CheckCollisionPointCircle(mousePosition, circle.position, circle.radius))
                    continue;

                selectedCircleID = circle.id;
                break;
            }
        }

        // Move Selected Circle
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectedCircleID >= 0)
        {
            Circle &circle = circles[selectedCircleID];
            circle.position = mousePosition;
        }

        // Release Moved Circle
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            selectedCircleID = -1;
        }

        // Launch Circle
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && selectedCircleID >= 0)
        {
            Circle &circle = circles[selectedCircleID];
            circle.velocity = Vector2Scale(Vector2Subtract(circle.position, mousePosition), 5.0f);

            selectedCircleID = -1;
        }

        // Update Circle Position
        for (Circle &circle : circles)
        {
            circle.acceleration = Vector2Scale(circle.velocity, -0.8f);
            circle.velocity = Vector2Add(circle.velocity, Vector2Scale(circle.acceleration, deltaTime));
            circle.position = Vector2Add(circle.position, Vector2Scale(circle.velocity, deltaTime));

            // Wrap Around the Window Edges
            if (circle.position.x < 0)
                circle.position = Vector2Add(circle.position, {windowWidth, 0.0f});
            if (circle.position.x >= windowWidth)
                circle.position = Vector2Subtract(circle.position, {windowWidth, 0.0f});
            if (circle.position.y < 0)
                circle.position = Vector2Add(circle.position, {0.0f, windowHeight});
            if (circle.position.y >= windowHeight)
                circle.position = Vector2Subtract(circle.position, {0.0f, windowHeight});

            float velocityMagnitude = Vector2Length(circle.velocity);
            if (velocityMagnitude < 0.1f)
                circle.velocity = Vector2Zero();
        }

        std::vector<std::pair<Circle &, Circle &>> collidingPairs;

        // Static Collision
        for (unsigned int i = 0; i < numCircles - 1; i++)
        {
            Circle &circle = circles[i];
            for (unsigned int j = i + 1; j < numCircles; j++)
            {
                Circle &other = circles[j];

                if (!CheckCollisionCircles(circle.position, circle.radius, other.position, other.radius))
                    continue;

                collidingPairs.push_back({circle, other});
                circle.resolveStaticCollision(other);
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto &circle : circles)
        {
            circle.draw();
        }

        for (auto &collidingPair : collidingPairs)
        {
            DrawLineV(collidingPair.first.position, collidingPair.second.position, RED);
        }

        if (selectedCircleID >= 0)
        {
            Circle &circle = circles[selectedCircleID];
            DrawLineV(circle.position, mousePosition, BLUE);
        }

        EndDrawing();
    }

    return 0;
}