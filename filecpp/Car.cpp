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
void Car::sound_object() {
    string MUSIC_PATH;
    
    MUSIC_PATH = "assets/Sound/car.ogg";
    Music car_Music;
    if (!car_Music.openFromFile(MUSIC_PATH)) {
        cout << "Loading music error\n";
    }
    car_Music.setVolume(100.f);
    car_Music.play();
    sf::sleep(sf::seconds(2.0f));
}
Rectangle Car::getrect() {
    return rec;
}