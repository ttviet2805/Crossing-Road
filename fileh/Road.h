#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Rectangle.h"
#include "Object.h"
#include "Mediator.h"
#include "Animal.h"
#include "TrafficLight.h"

using namespace sf;
using namespace std;

const string OBJECT_PATH = "assets/Image/Object/";

class Road {
private:
	Rectangle roadRect;
	vector <Object*> listObject;
	int roadState  = 0;
	double timeObjectRand;
	double timeGreenTrafficLight;
	double timeRedTraficLight = 3;
	Mediator* mediator;
	TrafficLight curLight;

	bool search = 0;
	bool isStop = 0;
	bool roadCount = 0;
	
	Texture carTexture;
	Texture trafficLightTexture[5];

	Clock trafficLightClock;
	Clock gameClock;

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
		timeObjectRand = randRealNumber(3, 7);
		timeGreenTrafficLight = randRealNumber(4, 10);
		
		carTexture.loadFromFile(OBJECT_PATH + "Car/Car.png");
	
		for (int i = 0; i < 3; i++) {
			if (!trafficLightTexture[i].loadFromFile(OBJECT_PATH + "Traffic-Light/Light" + to_string(i) + ".png")) {
				cout << "Loading image error\n";
			}
		}

		Vector2f curPos = roadRect.getPosition();

		if (roadState == 1) {
			Rectangle tmpRect(Vector2f(30, 90), Vector2f(curPos.x, curPos.y + 10), trafficLightTexture[0]);
			TrafficLight tmpLight(tmpRect);
			curLight = tmpLight;
		}
	}

	RectangleShape getRect() {
		return roadRect.getRect();
	}

	void generateObject(int state) {
		Object* curObject = nullptr;

		//cout << state << endl;

		Vector2f curPos = roadRect.getPosition();

		if (state == 2) {
			int tmpState = Rand(1, 2);
			if (tmpState == 1) {
				const string fileName = "assets/Image/Object/Dinosaur/";

				curObject = new Animal(Vector2f(100, 60), roadRect.getPosition(), 0.1, fileName, 12);

				listObject.push_back(curObject);
			}
			else {
				const string fileName = "assets/Image/Object/Dog/";

				curObject = new Animal(Vector2f(60, 100), roadRect.getPosition(), 0.1, fileName, 12);

				listObject.push_back(curObject);
			}
		}

		if (state == 1) {
			Rectangle tmpRect(Vector2f(100, 60), Vector2f(curPos.x + 30, curPos.y), carTexture);
			curObject = new Car(tmpRect, 0.1);

			listObject.push_back(curObject);
		}
	}

	void draw(sf::RenderWindow& window) {
		if (roadState) {
			Time elapsed = gameClock.getElapsedTime();
			if (elapsed.asSeconds() >= timeObjectRand && curLight.getState() == 0) {
				if (listObject.size() == 0) {
					generateObject(roadState);
					timeObjectRand = randRealNumber(3.5, 7);
					gameClock.restart();
				}
				else {
					if (listObject.back()->getRect().getPosition().x >= 150) {
						generateObject(roadState);
						timeObjectRand = randRealNumber(3.5, 7);
						gameClock.restart();
					}
				}
			}
		}

		if (roadState == 1) {
			if (curLight.getState() == 0) {
				Time elapsed = trafficLightClock.getElapsedTime();

				if (elapsed.asSeconds() >= timeGreenTrafficLight) {
					cout << "Red mode\n";
					curLight.setTexture(trafficLightTexture[2]);
					trafficLightClock.restart();
					curLight.changeType(2);
				}
			}
			else {
				if (curLight.getState() == 2) {
					Time elapsed = trafficLightClock.getElapsedTime();

					if (elapsed.asSeconds() >= timeRedTraficLight) {
						curLight.setTexture(trafficLightTexture[0]);
						trafficLightClock.restart();
						curLight.changeType(0);
					}
				}
			}
		}

		for (int i = 0; i < listObject.size(); i++) {
			if(curLight.getState() == 0) listObject[i]->move();
		}
			

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
			if (listObject[i]) {
				delete listObject[i];
			}
		//delete mediator;
	}
};