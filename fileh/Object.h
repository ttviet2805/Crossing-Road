#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "Rectangle.h"

const float MIN_DISTANCE = 12.5;

class Object {
private:
    Rectangle rec;
    float speed;
public:
    Object(Rectangle i_rec, float i_speed);
    bool collision(Rectangle src);
    void move();
    void setSpeed(float i_speed);
    Rectangle getrect();

    RectangleShape getRect() {
        return rec.getRect();
    }
};