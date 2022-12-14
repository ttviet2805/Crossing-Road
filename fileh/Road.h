#pragma once
#include <vector>
#include <../SFML/Graphics.hpp>
#include "Car.h"
#include "Rectangle.h"

using namespace sf;
using namespace std;

class Road {
private:
	Rectangle roadRect;
	double speed = 0;
	bool isStop = 0;
public:
	Road(Rectangle _Rect) {
		roadRect = _Rect;
		speed = 0;
		isStop = 0;
	}

	RectangleShape getRect() {
		return roadRect.getRect();
	}

	void draw(sf::RenderWindow& window) {
		window.draw(roadRect.getRect());
	}

	~Road() {}
};