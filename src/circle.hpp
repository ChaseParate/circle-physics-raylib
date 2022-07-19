#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class Circle
{
public:
    unsigned int id;
    Vector2 position;
    float radius;

    Circle(unsigned int id, Vector2 position, float radius) : id{id}, position{position}, radius{radius} {};

    void resolveStaticCollision(Circle &other);

    void draw();
};

#endif