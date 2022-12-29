#include <iostream>
#include "../fileh/Animal.h"

using namespace std;

Animal::Animal(Vector2f _size, Vector2f _pos, float i_speed, string _fileName, int _state, int _numTexture) {
    speed = i_speed;
    numTexture = _numTexture;
    curTexture = 0;
    state = _state;
    
    for (int i = 0; i < numTexture; i++) {
        if (!listTexture[i].loadFromFile(_fileName + "Animal" + to_string(i) + ".jpg")) {
            cout << "Loading Animal error\n";
        }

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
    if ((this->rec).isCollision(src) && srcPoint.y <= thisPoint.y) return true;
    else return false;
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

    animal_Music.play();
}
Rectangle Animal::getrect() {
    return rec;
}