#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Object.h"

class Car: public Object {
private:
    Rectangle rec;
    float speed;
public:
    Car(Rectangle i_rec, float i_speed);
    bool collision(Rectangle src);
    void move();
    void setSpeed(float i_speed);
    Rectangle getrect();
    void sound_object();
    RectangleShape getRect() {
        return rec.getRect();
    }

    void setPosition(Vector2f _pos) {
        rec.setPosition(_pos);
    }

    void draw(RenderWindow& window) {
        window.draw(rec.getRect());
    }
};