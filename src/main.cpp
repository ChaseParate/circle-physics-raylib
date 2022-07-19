#include <cstdio>
#include <vector>

#include <raylib.h>
#include <raymath.h>

class Circle
{
public:
    unsigned int id;
    Vector2 position;
    float radius;

    Circle(unsigned int id, Vector2 position, float radius) : id{id}, position{position}, radius{radius} {};

    bool collidePoint(Vector2 point)
    {
        float distance = Vector2Distance(position, point);
        return distance <= radius;
    }

    bool collideCircle(Circle &other)
    {
        float distance = Vector2Distance(position, other.position);
        return distance <= radius + other.radius;
    }

    void resolveStaticCollision(Circle &other)
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

    void draw()
    {
        DrawCircleLines(position.x, position.y, radius, GRAY);

        unsigned int fontSize = radius;
        const char *text = TextFormat("%d", id);
        unsigned int textWidth = MeasureText(text, fontSize);

        DrawText(text, position.x - (textWidth / 2), position.y - (fontSize / 2), fontSize, GRAY);
    }
};

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

    int selectedCircleID = -1;

    for (unsigned int i = 0; i < numCircles; i++)
    {
        float radius = GetRandomValue(25, 100);
        Vector2 position = {
            static_cast<float>(GetRandomValue(radius, windowWidth - radius)),
            static_cast<float>(GetRandomValue(radius, windowHeight - radius))};
        Circle circle = Circle(i, position, radius);

        circles.push_back(circle);
    }

    while (!WindowShouldClose())
    {
        // Update

        // Mouse Controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();

            selectedCircleID = -1;
            for (auto &circle : circles)
            {
                if (!circle.collidePoint(mousePosition))
                    continue;

                selectedCircleID = circle.id;
                break;
            }
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            selectedCircleID = -1;
        }

        if (selectedCircleID >= 0)
        {
            Circle &circle = circles[selectedCircleID];
            circle.position = GetMousePosition();
        }

        // Static Collision
        for (auto &circle : circles)
        {
            for (auto &other : circles)
            {
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

        EndDrawing();
    }

    return 0;
}