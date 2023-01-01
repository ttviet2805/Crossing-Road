#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Object_static.h"

class Rock : public Object_static {
private:
    Rectangle rec;
public:
    Rock(Rectangle i_rec);
    bool collision(Rectangle src);
    Rectangle getrect();

    RectangleShape getRect() {
        return rec.getRect();
    }

    void draw(RenderWindow& window) {
        window.draw(rec.getRect());
    }
};