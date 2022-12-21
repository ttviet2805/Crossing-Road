#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Rectangle.h"
#include "Object.h"
#include "Mediator.h"

using namespace sf;
using namespace std;

class Road {
private:
	Rectangle roadRect;
	bool search = 0;
	bool isStop = 0;
	bool roadCount = 0;
	vector <Object*> listObject;
	Texture dogTexture;
	bool isCarRoad = false;
	double timeRand = 3;
	Mediator* mediator;

public:
	int Rand(int l, int r) {
		return l + (rand()) % (r - l + 1);
	}

	float randRealNumber(float low, float high) {
		float r3 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));

		return r3;
	}

	Road(Rectangle _Rect, bool _isCarRoad, Mediator *mediator = nullptr) {
		cout << "Road spawn";
		roadRect = _Rect;
		isStop = 0;
		isCarRoad = _isCarRoad;
		dogTexture.loadFromFile("assets/image/Car.png");
		this->mediator = mediator;
	}

	RectangleShape getRect() {
		return roadRect.getRect();
	}

	void generateObject() {
		Rectangle dogRect(Vector2f(100, 60), roadRect.getPosition(), dogTexture);

		Object* curObject = new Car(dogRect, 0.1);
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

	bool startSearch(Rectangle src) {
		this->search = this->roadRect.isCollision(src);
		if (this->search) {
			for (int i = 0; i < (int)this->listObject.size(); i++) {
				if (this->listObject[i]->collision(src)) {
					cout << "Collision\n";
					return true;
				}
			}
		}
		return false;
	}

	~Road() {}
};