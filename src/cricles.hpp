#pragma once
#include <raylib.h>

class cricles
{
public:
    Vector2 position;
    float radius;
    bool highlighted;
    bool collided;
    cricles(Vector2 position, float radius){
        highlighted = false;
        collided = false;
        this->position = position;
        this->radius = radius;
    }

    void draw()
    {
        if (highlighted)
        {
            DrawCircleV(position, radius, GREEN);
        }
        else
        {
            DrawCircleV(position, radius, WHITE);
        }
    }

    void update()
    {
        position.x += GetRandomValue(-2, 2);
        position.y += GetRandomValue(-2, 2);
    }
    ~cricles() {}
};
