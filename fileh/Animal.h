#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "Object.h"

class Animal: public Object {
private:
    Rectangle rec;
    float speed;
    Clock clock;
    double timeChangeFrame = 0.1;
    int numTexture;
    int curTexture = 0;
    Texture listTexture[20];
    Rectangle listRect[20];
    
    // = 0 if dinosaur
    // = 1 if dog
    int state;
public:
    Animal(Vector2f _size, Vector2f _pos, float i_speed, string _fileName, int _state, int _numTexture);
    bool collision(Rectangle src);
    void move();
    void setSpeed(float i_speed);
    Rectangle getrect();
    void sound_object();
    RectangleShape getRect() {
        return rec.getRect();
    }

    void draw(RenderWindow& window) {
        listRect[curTexture].setPosition(rec.getPosition());

        window.draw(listRect[curTexture].getRect());
    }
};