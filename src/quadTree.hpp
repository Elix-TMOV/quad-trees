#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
#include <list>

using namespace std;


class quadTree
{
private:
    Rectangle boundaryBox;
    quadTree* nw = nullptr;
    quadTree* ne = nullptr;
    quadTree* se = nullptr;
    quadTree* sw = nullptr;
    bool devided;
    vector<Vector2*> items;
    static int capacity;

    void subDevide() {
        // Northeast rectangle
        Rectangle neRect = {
            boundaryBox.x + boundaryBox.width / 2,
            boundaryBox.y,
            boundaryBox.width / 2,
            boundaryBox.height / 2
        };

        // Southeast rectangle
        Rectangle seRect = {
            boundaryBox.x + boundaryBox.width / 2,
            boundaryBox.y + boundaryBox.height / 2,
            boundaryBox.width / 2,
            boundaryBox.height / 2
        };

        // Southwest rectangle
        Rectangle swRect = {
            boundaryBox.x,
            boundaryBox.y + boundaryBox.height / 2,
            boundaryBox.width / 2,
            boundaryBox.height / 2
        };

        // Northwest rectangle
        Rectangle nwRect = {
            boundaryBox.x,
            boundaryBox.y,
            boundaryBox.width / 2,
            boundaryBox.height / 2
        };

        // Create new quadTree nodes
        ne = new quadTree(neRect);
        se = new quadTree(seRect);
        sw = new quadTree(swRect);
        nw = new quadTree(nwRect);

        devided = true;
    }

public:
    quadTree(Rectangle boundaryBox) {
        this->boundaryBox = boundaryBox;
        devided = false;
        items = {};
    }

    ~quadTree() {
        // Destructor implementation
        if (nw) {
            delete nw;
            nw = nullptr;
        }
        if (ne) {
            delete ne;
            ne = nullptr;
        }
        if (sw) {
            delete sw;
            sw = nullptr;
        }
        if (se) {
            delete se;
            se = nullptr;
        }
    }
    

    void draw(){
        DrawRectangleLines(boundaryBox.x, boundaryBox.y, boundaryBox.width, boundaryBox.height, WHITE);
        if (devided){
            ne->draw();
            nw->draw();
            sw->draw();
            se->draw();
        }
    }

    void insert(Vector2* point) {
        if (!CheckCollisionPointRec(*point, boundaryBox)){
            return;
        }
        // Implementation
        if (items.size() < capacity){
            items.push_back(point);
            // cout << point->x << point->y << endl;
            // cout << "0th element " << items.front()->x << items.front()->y << endl;
        }
        else {
            // time to sub devide the distribute the stuff there
            if (!devided){
                subDevide();
            }
            ne->insert(point);
            nw->insert(point);
            sw->insert(point);
            se->insert(point);
        }
    }
    
    void query(Vector3 circle, vector<Vector2*>* objects) {
        if (CheckCollisionCircleRec({circle.x, circle.y}, circle.z, boundaryBox)) {
            for (auto& item : items) {
                if (CheckCollisionPointCircle(*item, {circle.x, circle.y}, circle.z)){
                    objects->push_back(item);
                }
            }

            if (devided) {
                ne->query(circle, objects);
                nw->query(circle, objects);
                se->query(circle, objects);
                sw->query(circle, objects);
            }
            return;
        }
    }
};

// Initialize static member
int quadTree::capacity = 10;


