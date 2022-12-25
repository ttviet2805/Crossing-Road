#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"

class TrafficLight {
private:
    Rectangle rect;
    bool isOn = false;
public:
    TrafficLight() {

    }

    TrafficLight(Rectangle _rect) {
        rect = _rect;
    }

    void setTrafficLight(Vector2f _size, Vector2f _pos, Texture& _Texture) {
        rect.setSize(_size);
        rect.setPosition(_pos);
        rect.setTexture(_Texture);
    }

     RectangleShape getRect() {
         return rect.getRect();
     }

    void changeType(bool type);
    void notify();
};