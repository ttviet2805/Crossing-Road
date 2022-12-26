#include <iostream>
#include "../fileh/Dinosaur.h"

using namespace std;

Dinosaur::Dinosaur(Vector2f _size, Vector2f _pos, float i_speed, string _fileName, int _numTexture) {
    speed = i_speed;
    numTexture = _numTexture;
    curTexture = 0;
    
    for (int i = 0; i < numTexture; i++) {
        if (!listTexture[i].loadFromFile(_fileName + "Dinosaur" + to_string(i) + ".jpg")) {
            cout << "Loading dinosaur error\n";
        }
    }

    rec.setSize(_size);
    rec.setPosition(_pos);
    rec.setTexture(listTexture[0]);
}
bool Dinosaur::collision(Rectangle src) {
    Vector2f srcPoint = src.getPosition();
    Vector2f thisPoint = (this->rec).getPosition();
    if ((this->rec).isCollision(src) && srcPoint.y <= thisPoint.y) return true;
    else return false;
}

void Dinosaur::move() {
    rec.move(speed, 0);

    Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= timeChangeFrame) {
        clock.restart();
        curTexture = (curTexture + 1) % numTexture;
        rec.setTexture(listTexture[curTexture]);
    }
}
void Dinosaur::setSpeed(float i_speed) {
    speed = i_speed;
}
Rectangle Dinosaur::getrect() {
    return rec;
}