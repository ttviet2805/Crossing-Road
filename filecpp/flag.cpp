#include "../fileh/flag.h"

using namespace std;

Flag::Flag() {

}

Flag::Flag(Rectangle i_rec) {
    rec = i_rec;
}

bool Flag::collision(Rectangle src) {
    Vector2f srcPoint = src.getPosition();
    Vector2f thisPoint = (this->rec).getPosition();
    if ((this->rec).isCollision(src) && srcPoint.y <= thisPoint.y) return true;
    else return false;
}

Rectangle Flag::getrect() {
    return rec;
}