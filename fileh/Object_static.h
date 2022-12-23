#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "Rectangle.h"

const float MIN_DISTANCE = 12.5;

class Object_static {
public:
    virtual bool collision(Rectangle src) = 0;
    virtual Rectangle getrect() = 0;

    virtual RectangleShape getRect() = 0;
};