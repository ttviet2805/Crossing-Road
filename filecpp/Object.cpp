#include <iostream>
#include "../fileh/Object.h"
using namespace std;

Object::Object(Rectangle i_rec, float i_speed){
    rec = i_rec;
    speed = i_speed;
}

bool Object::collision(Rectangle src){
    return rec.isCollision(src);
}

void Object::move(){
    rec.move(speed, 0);
}
void Object::setSpeed(float i_speed){
    speed = i_speed;
}
Rectangle Object::getrect(){
    return rec;
}