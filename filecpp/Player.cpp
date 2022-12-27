#include "../fileh/Player.h"

void Player::changeSpeed(float speed) {
    curSpeed += speed;
}

void Player::updateInfo(std::string newName) {
    name=newName;
}