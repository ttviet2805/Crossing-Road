#include <iostream>
#include "../fileh/Rock.h"

using namespace std;

Rock::Rock(Rectangle i_rec) {
    rec = i_rec;
}
bool Rock::collision(Rectangle src) {
    Vector2f srcPoint = src.getPosition();
    Vector2f thisPoint = (this->rec).getPosition();

    float dis = ((srcPoint.x - thisPoint.x) * (srcPoint.x - thisPoint.x) + (srcPoint.y - thisPoint.y) * (srcPoint.y - thisPoint.y));
    dis = sqrt(dis);
    if ((this->rec).isCollision(src) && srcPoint.y <= thisPoint.y) {
        //cout << dis << '\n';
        if (dis <= MIN_DIS) {
            return true;
        }
    }
    return false;
}

Rectangle Rock::getrect() {
    return rec;
}