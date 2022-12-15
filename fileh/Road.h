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

public:
	Road(Rectangle _Rect) {
		roadRect = _Rect;
		isStop = 0;
		dogTexture.loadFromFile("assets/image/Car.png");
	}

	RectangleShape getRect() {
		return roadRect.getRect();
	}

	void generateObject() {
		Rectangle dogRect(Vector2f(100, 60), roadRect.getPosition(), dogTexture);

		Object* curObject = new Object(dogRect, 0.2);
		listObject.push_back(curObject);
	}

	void draw(sf::RenderWindow& window) {
		for (auto i : listObject) {
			i->move();
		}

		window.draw(roadRect.getRect());

		for (auto i : listObject) {
			window.draw(i->getRect());
		}
	}

	~Road() {}
};