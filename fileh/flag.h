#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Object_static.h"

class Flag : public Object_static {
private:
    Rectangle rec;
public:
    Flag(Rectangle i_rec);
    bool collision(Rectangle src);
    Rectangle getrect();

    RectangleShape getRect() {
        return rec.getRect();
    }
};