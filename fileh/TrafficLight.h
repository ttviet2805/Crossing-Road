#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"

class TrafficLight {
private:
    Rectangle rect;
    int state = 0;
public:
    TrafficLight() {

    }

    TrafficLight(Rectangle _rect) {
        rect = _rect;
    }

    void setTexture(Texture& _texture) {
        rect.setTexture(_texture);
    }

     RectangleShape getRect() {
         return rect.getRect();
     }

    void changeType(int type);

    int getState() {
        return state;
    }
    void notify();
};