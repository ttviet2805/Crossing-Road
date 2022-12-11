#pragma once
#include <vector>
#include "Car.h"
#include <../SFML/Graphics.hpp>

class Road {
private:
	sf::Vector2f position;
	sf::Texture road;
	sf::RectangleShape sprite;
	//sf::IntRect sourceRect;
	std::vector<Car*> cars;
public:
	Road() : position(sf::Vector2f(0, 0)) { initRoad(); }

	Road(float x, float y) : position(sf::Vector2f(x, y)) { initRoad(); }

	void initRoad() {
		this->road.loadFromFile("image/Road_long.jpg", sf::IntRect(0, 327, 1780, 160));
		this->sprite.setSize(sf::Vector2f(1760, 160));
		this->sprite.setPosition(this->position);
		this->sprite.setTexture(&this->road);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(this->sprite);
	}

	virtual ~Road() {
	}
};