#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
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
};