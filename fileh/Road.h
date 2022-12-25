#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Rectangle.h"
#include "Object.h"
#include "Mediator.h"
#include "Dinosaur.h"
#include "TrafficLight.h"

using namespace sf;
using namespace std;

const string OBJECT_PATH = "assets/Image/Object/";

class Road {
private:
	Rectangle roadRect;
	bool search = 0;
	bool isStop = 0;
	bool roadCount = 0;
	vector <Object*> listObject;
	int roadState  = 0;
	double timeRand = 3;
	Mediator* mediator;
	TrafficLight curLight;
	
	Texture carTexture;
	Texture dinosaurTexture[15];
	Texture trafficLightTexture[5];

public:
	int Rand(int l, int r) {
		return l + (rand()) % (r - l + 1);
	}

	float randRealNumber(float low, float high) {
		float r3 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));

		return r3;
	}

	Road(Rectangle _Rect, int _roadState, Mediator *mediator = nullptr) {
		cout << "Road spawn";
		roadRect = _Rect;
		isStop = 0;
		roadState = _roadState;
		this->mediator = mediator;
		timeRand = randRealNumber(3, 7);
		
		carTexture.loadFromFile(OBJECT_PATH + "Car/Car.png");
		
		for(int i = 0; i <= 12; i++)
			dinosaurTexture[i].loadFromFile(OBJECT_PATH + "Dinosaur/Dinosaur" + to_string(i) + ".jpg");
	
		for (int i = 0; i < 3; i++) {
			if (!trafficLightTexture[i].loadFromFile(OBJECT_PATH + "Traffic-Light/Light" + to_string(i) + ".png")) {
				cout << "Loading image error\n";
			}
		}

		Vector2f curPos = roadRect.getPosition();

		Rectangle tmpRect(Vector2f(30, 90), Vector2f(curPos.x, curPos.y + 10), trafficLightTexture[0]);
		TrafficLight tmpLight(tmpRect);
		curLight = tmpLight;
	}

	RectangleShape getRect() {
		return roadRect.getRect();
	}

	void generateObject(int state) {
		Object* curObject = nullptr;

		//cout << state << endl;

		if (state == 2) {
			Rectangle tmpRect(Vector2f(100, 60), roadRect.getPosition(), dinosaurTexture[0]);
			curObject = new Dinosaur(tmpRect, 0.1);

			listObject.push_back(curObject);
		}

		if (state == 1) {
			Rectangle tmpRect(Vector2f(100, 60), roadRect.getPosition(), carTexture);
			curObject = new Car(tmpRect, 0.1);

			listObject.push_back(curObject);
		}
	}

	void draw(sf::RenderWindow& window, Clock& clock) {
		if (roadState) {
			Time elapsed = clock.getElapsedTime();
			if (elapsed.asSeconds() >= timeRand) {
				generateObject(roadState);
				timeRand = randRealNumber(3.5, 7);
				clock.restart();
			}
		}

		for (int i = 0; i < listObject.size(); i++)
			listObject[i]->move();

		window.draw(roadRect.getRect());
		window.draw(curLight.getRect());

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

	~Road() {
		for (int i = 0; i < listObject.size(); i++)
			delete listObject[i];

		delete mediator;
	}
};