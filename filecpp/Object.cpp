#include "../fileh/Object.h"
using namespace std;

Object::Object(Rectangle i_rec, float i_speed){
    rec = i_rec;
    speed = i_speed;
}

bool Object::collision(Rectangle src){
    Vector2f srcPoint = src.getPosition();
    srcPoint = Vector2f(srcPoint.x + src.getSize().x / 2, srcPoint.y + src.getSize().y / 2);
    Vector2f point = this->rec.getPosition();
    point = Vector2f(point.x + this->rec.getSize().x / 2, point.y + this->rec.getSize().y / 2);
    float distance = sqrt((srcPoint.x - point.x) * (srcPoint.x - point.x) - (srcPoint.y - point.y) * (srcPoint.y - point.y));
    //cout << distance << '\n';

    return distance < (src.getSize().x / 1.25);
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