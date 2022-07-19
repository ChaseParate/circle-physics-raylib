#include <array>
#include <cstdio>

#include <raylib.h>
#include <raymath.h>

struct Circle
{
    unsigned int id;

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
        circle.id = i;
        circle.radius = static_cast<float>(GetRandomValue(25, 100));
        circle.position = {
            static_cast<float>(GetRandomValue(circle.radius, windowWidth - circle.radius)),
            static_cast<float>(GetRandomValue(circle.radius, windowHeight - circle.radius))};

        circles[i] = circle;
    }

    while (!WindowShouldClose())
    {
        // Update
        for (auto &circle : circles)
        {
            for (auto &other : circles)
            {
                if (circle.id == other.id)
                    continue;

                float distance = Vector2Distance(circle.position, other.position);
                if (distance >= circle.radius + other.radius)
                    continue;

                float overlap = (distance - circle.radius - other.radius) / 2;
                // std::printf("IDs: %d, %d\tRadii: %.1f, %.1f\tDistance: %.2f \tOverlap: %.2f\n",
                //             circle.id, other.id, circle.radius, other.radius, distance, overlap);

                Vector2 deltaPosition = Vector2Subtract(circle.position, other.position);
                Vector2 moveAmount = Vector2Scale(deltaPosition, overlap / distance);

                circle.position = Vector2Subtract(circle.position, moveAmount);
                other.position = Vector2Add(other.position, moveAmount);
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (auto &circle : circles)
        {
            DrawCircleLines(circle.position.x, circle.position.y, circle.radius, GRAY);

            unsigned int fontSize = circle.radius;
            const char *text = TextFormat("%d", circle.id);
            unsigned int textWidth = MeasureText(text, fontSize);

            DrawText(text,
                     circle.position.x - (textWidth / 2),
                     circle.position.y - (fontSize / 2),
                     fontSize,
                     GRAY);
        }

        EndDrawing();
    }

    return 0;
}