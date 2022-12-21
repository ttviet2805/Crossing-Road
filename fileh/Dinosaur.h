#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Object.h"
class Dinosaur: public Object {
private:
    Rectangle rec;
    float speed;
public:
    Dinosaur(Rectangle i_rec, float i_speed);
    bool collision(Rectangle src);
    void move();
    void setSpeed(float i_speed);
    Rectangle getrect();

    RectangleShape getRect() {
        return rec.getRect();
    }
};