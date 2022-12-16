#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Rectangle.h"
#include "Object.h"

using namespace sf;
using namespace std;

class Road {
private:
	Rectangle roadRect;
	bool isStop = 0;
	vector <Object*> listObject;
	Texture dogTexture;
	bool isCarRoad = false;
	double timeRand = 3;

public:
	int Rand(int l, int r) {
		return l + (rand()) % (r - l + 1);
	}

	float randRealNumber(float low, float high) {
		float r3 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));

		return r3;
	}

	Road(Rectangle _Rect, bool _isCarRoad) {
		roadRect = _Rect;
		isStop = 0;
		isCarRoad = _isCarRoad;
		dogTexture.loadFromFile("assets/image/Car.png");
	}

	RectangleShape getRect() {
		return roadRect.getRect();
	}

	void generateObject() {
		Rectangle dogRect(Vector2f(100, 60), roadRect.getPosition(), dogTexture);

		Object* curObject = new Object(dogRect, 0.1);
		listObject.push_back(curObject);
	}

	void draw(sf::RenderWindow& window, Clock& clock) {
		if (isCarRoad) {
			Time elapsed = clock.getElapsedTime();
			if (elapsed.asSeconds() >= timeRand) {
				generateObject();
				timeRand = randRealNumber(3, 10);
				clock.restart();
			}
		}

		for (int i = 0; i < listObject.size(); i++)
			listObject[i]->move();

		window.draw(roadRect.getRect());

		for (int i = 0; i < listObject.size(); i++) {
			window.draw(listObject[i]->getRect());
		}
	}

	~Road() {}
};