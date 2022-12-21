#include <iostream>
#include "../fileh/Dinosaur.h"

using namespace std;

Dinosaur::Dinosaur(Rectangle i_rec, float i_speed) {
    rec = i_rec;
    speed = i_speed;
}
bool Dinosaur::collision(Rectangle src) {
    Vector2f srcPoint = src.getPosition();
    Vector2f thisPoint = (this->rec).getPosition();
    if ((this->rec).isCollision(src) && srcPoint.y >= thisPoint.y) return true;
    else return false;
}

void Dinosaur::move() {
    rec.move(speed, 0);
}
void Dinosaur::setSpeed(float i_speed) {
    speed = i_speed;
}
Rectangle Dinosaur::getrect() {
    return rec;
}