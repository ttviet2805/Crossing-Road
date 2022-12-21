#include <iostream>
#include "../fileh/Car.h"

using namespace std;

Car::Car(Rectangle i_rec, float i_speed) {
    rec = i_rec;
    speed = i_speed;
}
bool Car::collision(Rectangle src) {
    Vector2f srcPoint = src.getPosition();
    Vector2f thisPoint = (this->rec).getPosition();
    if ((this->rec).isCollision(src) && srcPoint.y <= thisPoint.y) return true;
    else return false;
}

void Car::move() {
    rec.move(speed, 0);
}
void Car::setSpeed(float i_speed) {
    speed = i_speed;
}
Rectangle Car::getrect() {
    return rec;
}