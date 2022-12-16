#include "../fileh/Player.h"

void Player::changeSpeed(float speed) {
    curSpeed=speed;
}

void Player::move(int direction) {
    switch(direction) {
        case 1: // move up
            //curPos.moveUp(curSpeed);
            break;
        case 2: // move down
            //curPos.moveDown(curSpeed);
            break;
        case 3: // move left
            //curPos.moveLeft(curSpeed);
            break;
        case 4: // move right
            //curPos.moveRight(curSpeed);
            break;
        default:
            break;
    }

    // Notify new position of player to observer;
    //observer->notify(curPos);
}

void Player::updateInfo(std::string newName) {
    name=newName;
}