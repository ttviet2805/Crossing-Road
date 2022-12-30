#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Rectangle.h"
#include "Object.h"
#include "Mediator.h"
#include "Animal.h"
#include "TrafficLight.h"
#include "AllTexture.h"

using namespace sf;
using namespace std;

const string OBJECT_PATH = "assets/Image/Object/";

class Road {
private:
	// Road Properties
	Rectangle roadRect;
	// 0 = Pavement
	// 1 = Street
	// 2 = Sand
	int roadState = 0;
	double timeObjectRand;
	Clock gameClock;
	// 0 = left to right
	// 1 = right to left
	int roadDirection;
	const int MAX_NUM_OBJECT = 2;

	// Object Properties
	vector <Object*> listObject;
	Texture carTexture;
	double objectSpeed;
	Texture animalTexture[2][20];
	// = 0 if dinosaur
	// = 1 if dog

	// Traffic light
	double timeGreenTrafficLight;
	double timeRedTraficLight = 3;
	Clock trafficLightClock;
	Texture trafficLightTexture[5];
	Rectangle redLightRect;
	Rectangle greenLightRect;
	TrafficLight curLight;

	// Mediator
	Mediator* mediator;
	bool search = 0;

public:
	int randIntegerNumber(int l, int r) {
		return l + (rand()) % (r - l + 1);
	}

	float randRealNumber(float low, float high) {
		float r3 = low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));

		return r3;
	}

	Road(Rectangle _Rect, int _roadState, double _objectSpeed, ListTexture* &gameTexture, Mediator* mediator = nullptr) {
		// Road Properties
		roadRect = _Rect;
		roadState = _roadState;
		timeObjectRand = randRealNumber(3, 7);
		roadDirection = randIntegerNumber(0, 1);
		if (roadDirection == 0)
			objectSpeed = _objectSpeed;
		else objectSpeed = -_objectSpeed;

		// Set up animal
		if (roadDirection == 0) {
			for (int i = 0; i < gameTexture->NUM_ANIMAL_TEXTURE; i++) {
				animalTexture[0][i] = gameTexture->animalTextureLeftRight[0][i];
				animalTexture[1][i] = gameTexture->animalTextureLeftRight[1][i];
			}
		}
		else {
			for (int i = 0; i < gameTexture->NUM_ANIMAL_TEXTURE; i++) {
				animalTexture[0][i] = gameTexture->animalTextureRightLeft[0][i];
				animalTexture[1][i] = gameTexture->animalTextureRightLeft[1][i];
			}
		}

		// Set up Car
		if (roadDirection == 0)
			carTexture = gameTexture->carTextureLeftRight;
		else {
			carTexture = gameTexture->carTextureRightLeft;
		}

		Vector2f curPos = roadRect.getPosition();

		// Set up Traffic Light
		for (int i = 0; i < 3; i++) {
			trafficLightTexture[i] = gameTexture->trafficLightTexture[i];
		}

		timeGreenTrafficLight = randRealNumber(4, 10);

		if (roadState == 1) {
			greenLightRect.setSize(Vector2f(25, 70));
			greenLightRect.setPosition(Vector2f(curPos.x, curPos.y + 10));
			greenLightRect.setTexture(trafficLightTexture[0]);

			redLightRect.setSize(Vector2f(25, 70));
			redLightRect.setPosition(Vector2f(curPos.x, curPos.y + 10));
			redLightRect.setTexture(trafficLightTexture[2]);
		}

		// Set Mediator
		this->mediator = mediator;
	}

	RectangleShape getRect() {
		return roadRect.getRect();
	}

	void generateObject(int state) {
		Object* curObject = nullptr;

		Vector2f roadPos = roadRect.getPosition();

		if (state == 2) {
			int animalState = randIntegerNumber(0, 1);
			
			// Dinosaur
			if (animalState == 0) {
				if (roadDirection) roadPos.x = GAME_WIDTH;

				curObject = new Animal(Vector2f(100, 60), roadPos, objectSpeed, 0, 12, animalTexture[0]);

				listObject.push_back(curObject);
			}
			// Dog
			else {
				if (roadDirection) roadPos.x = GAME_WIDTH;

				curObject = new Animal(Vector2f(60, 100), roadPos, objectSpeed, 0, 12, animalTexture[1]);

				listObject.push_back(curObject);
			}
		}

		if (state == 1) {
			Rectangle tmpRect(Vector2f(100, 60), Vector2f(roadPos.x + 30, roadPos.y), carTexture);
			if (roadDirection) {
				tmpRect.setPosition(Vector2f(GAME_WIDTH - 30, roadPos.y));
			}

			curObject = new Car(tmpRect, objectSpeed);

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
					if (listObject.size() > MAX_NUM_OBJECT) {
						gameClock.restart();
						timeObjectRand = randRealNumber(3.5, 7);
					}
					else {
						if (roadDirection == 0 && listObject.back()->getRect().getPosition().x >= 250) {
							generateObject(roadState);
							timeObjectRand = randRealNumber(3.5, 7);
							gameClock.restart();
						}
						if (roadDirection == 1 && listObject.back()->getRect().getPosition().x <= GAME_WIDTH - 250) {
							generateObject(roadState);
							timeObjectRand = randRealNumber(3.5, 7);
							gameClock.restart();
						}
					}
				}
			}
		}

		if (roadState == 1) {
			if (curLight.getState() == 0) {
				Time elapsed = trafficLightClock.getElapsedTime();

				if (elapsed.asSeconds() >= timeGreenTrafficLight) {
					trafficLightClock.restart();
					curLight.changeType(2);
				}
			}
			else {
				if (curLight.getState() == 2) {
					Time elapsed = trafficLightClock.getElapsedTime();

					if (elapsed.asSeconds() >= timeRedTraficLight) {
						trafficLightClock.restart();
						curLight.changeType(0);
					}
				}
			}
		}

		while (listObject.size() > 0) {
			bool state = true;

			for (int i = 0; i < listObject.size(); i++) {
				if (listObject[i]->getRect().getPosition().x > GAME_WIDTH) {
					state = false;
					listObject.erase(listObject.begin() + i, listObject.begin() + i + 1);
					break;
				}

				if (listObject[i]->getRect().getPosition().x < 0) {
					state = false;
					listObject.erase(listObject.begin() + i, listObject.begin() + i + 1);
					break;
				}
			}

			if (state) break;
		}


		for (int i = 0; i < listObject.size(); i++) {
			if (curLight.getState() == 0) listObject[i]->move();
		}


		window.draw(roadRect.getRect());

		for (int i = 0; i < listObject.size(); i++) {
			listObject[i]->draw(window);
		}

		if (curLight.getState() == 0) {
			window.draw(greenLightRect.getRect());
		}
		else {
			if (curLight.getState() == 2) {
				window.draw(redLightRect.getRect());
			}
		}
	}

	int startSearch(Rectangle src) {
		this->search = this->roadRect.isCollision(src);
		if (this->search) {
			for (int i = 0; i < (int)this->listObject.size(); i++) {
				if (this->listObject[i]->collision(src)) {
					cout << "Road Collision\n";
					//auto pos = this->getRect().getPosition();
					//this->mediator->returnLastPos(pos.x, pos.y);
					return 2;
				}
			}
			return (this->roadState == 0);
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