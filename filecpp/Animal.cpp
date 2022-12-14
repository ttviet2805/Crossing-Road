#include <iostream>
#include "../fileh/Animal.h"

using namespace std;

Animal::Animal(Vector2f _size, Vector2f _pos, float i_speed, int _state, int _numTexture, Texture listTexture[20]) {
    speed = i_speed;
    numTexture = _numTexture;
    curTexture = 0;
    state = _state;
    
    for (int i = 0; i < numTexture; i++) {
        listRect[i].setSize(_size);
        listRect[i].setPosition(_pos);
        listRect[i].setTexture(listTexture[i]);
    }

    rec.setSize(_size);
    rec.setPosition(_pos);
    rec.setTexture(listTexture[0]);
}
bool Animal::collision(Rectangle src) {
    Vector2f srcPoint = src.getPosition();
    Vector2f thisPoint = (this->rec).getPosition();

    float dis = ((srcPoint.x - thisPoint.x) * (srcPoint.x - thisPoint.x) + (srcPoint.y - thisPoint.y) * (srcPoint.y - thisPoint.y));
    dis = sqrt(dis);
    if ((this->rec).isCollision(src) && srcPoint.y <= thisPoint.y) {
        if (dis <= MIN_DISTANCE) {
            return true;
        }
    }
    return false;
}

void Animal::move() {
    rec.move(speed, 0);

    Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= timeChangeFrame) {
        clock.restart();
        curTexture = (curTexture + 1) % numTexture;
    }
}
void Animal::setSpeed(float i_speed) {
    speed = i_speed;
}
void Animal::sound_object() {
    string MUSIC_PATH;
    if(state == 1)
        MUSIC_PATH = "assets/Sound/dog_bark.ogg";
    else MUSIC_PATH = "assets/Sound/dinosaur_bark.ogg";
    Music animal_Music;
    if (!animal_Music.openFromFile(MUSIC_PATH)) {
        cout << "Loading music error\n";
    }
    animal_Music.setVolume(100.f);
    animal_Music.play();
    sf::sleep(sf::seconds(2.0f));
}
Rectangle Animal::getrect() {
    return rec;
}