#pragma once
#include <SFML/Graphics.hpp>
#include "Road.h"

class TrafficLight{
private:
    Road* road;
    bool isOn;
public:
    void changeType(bool type);
    void notify();
};