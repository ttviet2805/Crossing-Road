#include <iostream>
#include "../fileh/Rock.h"

using namespace std;

Rock::Rock(Rectangle i_rec) {
    rec = i_rec;
}
bool Rock::collision(Rectangle src) {
    Vector2f srcPoint = src.getPosition();
    Vector2f thisPoint = (this->rec).getPosition();
    if ((this->rec).isCollision(src) && srcPoint.y <= thisPoint.y) return true;
    else return false;
}

Rectangle Rock::getrect() {
    return rec;
}