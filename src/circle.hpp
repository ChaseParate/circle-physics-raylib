#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class Circle
{
public:
    unsigned int id;
    float radius;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Circle(unsigned int id, float radius, Vector2 position) : id{id}, radius{radius}, position{position}
    {
        velocity = Vector2Zero();
        acceleration = Vector2Zero();
    };

    void resolveStaticCollision(Circle &other);

    void draw();
};

#endif