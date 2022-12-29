#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "Rectangle.h"

const float MIN_DISTANCE = 12.5;

class Object {
public:
    virtual bool collision(Rectangle src) = 0;
    virtual void move() = 0;
    virtual void setSpeed(float i_speed) = 0;
    virtual Rectangle getrect() = 0;
    virtual void sound_object() = 0;
    virtual RectangleShape getRect() = 0;
    virtual void draw(RenderWindow& window) = 0;
};