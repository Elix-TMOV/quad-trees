#include <raylib.h>
#include "quadTree.hpp"
#include <iostream>
#include <list>
#include "cricles.hpp"

using namespace std;

int main(){
    int width = 1000;
    int height = 800;
    list<cricles> points;
    InitWindow(width, height, "quadTrees");
    SetTargetFPS(60);
    
    for (int i = 0; i < 1000; i++){
        Vector2 randomPoint = {(float)GetRandomValue(0, width), (float)GetRandomValue(0, height)};
        points.push_back(cricles(randomPoint, 10));
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(BLACK);

        // Clear and reinsert points into the quadtree
        quadTree* tree = new quadTree({0, 0, width, height});

        for (auto it = points.begin(); it != points.end();){
            it->draw();
            it->update();
            tree->insert(&(it->position));
            if (it->collided) {
                it = points.erase(it); // Remove from list and get next iterator
            } else {
                ++it; // Move to next iterator
            }
        }

        for (auto& point: points){
            vector<Vector2*> objects = {};
            tree->query(Vector3{point.position.x, point.position.y, point.radius*2}, &objects);
            for (auto object: objects){
                if (&(point.position) != object && CheckCollisionCircles({point.position.x, point.position.y}, point.radius, {object->x, object->y}, point.radius)){
                    point.highlighted = true;
                    point.collided = true;
                }
            }
        }

        delete tree;
        EndDrawing();
    }

    CloseWindow();
}
