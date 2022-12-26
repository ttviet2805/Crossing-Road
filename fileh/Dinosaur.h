#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Object.h"
class Dinosaur: public Object {
private:
    Rectangle rec;
    float speed;
    Clock clock;
    double timeChangeFrame = 0.1;
    int numTexture;
    int curTexture = 0;
    Texture listTexture[20];
public:
    Dinosaur(Vector2f _size, Vector2f _pos, float i_speed, string _fileName, int _numTexture);
    bool collision(Rectangle src);
    void move();
    void setSpeed(float i_speed);
    Rectangle getrect();

    RectangleShape getRect() {
        return rec.getRect();
    }
};