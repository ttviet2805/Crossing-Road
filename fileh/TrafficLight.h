#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"

class TrafficLight {
private:
    int state = 0;
public:
    TrafficLight() {

    }

    void changeType(int type);

    int getState() {
        return state;
    }
    void notify();
};