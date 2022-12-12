#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Object.h"
class Dinosaur: public Object {
public:
    Dinosaur(Rectangle rec, float speed);
};