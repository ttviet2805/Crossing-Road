#pragma once
#include <iostream>
#include <vector>
#include <../SFML/Graphics.hpp>
#include "Road.h"
#include "Player.h"
#include "State.h"

class Level : public State {
private:
	float deltaTime;

	std::vector<Road*> roads;

	sf::Clock clock;
public:

	void initBackground(int x, int y) {
		if (!this->backgroundImg.create(x, y)) {
			//lol
		}

		if (!this->texture.loadFromFile("image/background.jpg")) {
			std::cout << "Dumb fuck\n";
		}
		this->addRoad(0, 100); this->addRoad(0, 300); this->addRoad(0, 500);
		this->loadSprite = sf::Sprite(this->texture);
		this->backgroundImg.draw(this->loadSprite);
	}

	Level() : State(0, 0, nullptr), deltaTime(10) {

	}

	Level(int x, int y, sf::RenderWindow* window) : State(x, y, window), deltaTime(10) {
		this->initBackground(x, y);
	}

	int run(Player* player) {

		auto subDeltaTime = this->clock.restart().asSeconds();
		if (subDeltaTime > 1.0f / 60.0f) {
			subDeltaTime = 1.0f / 60.0f;
		}

		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return 0;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					return 0;
				}
				player->updatePos(event, this->deltaTime);
			}
		}

		player->updateSprite(subDeltaTime);

		this->window->clear(sf::Color::Black);
		this->window->draw(this->loadSprite);
		for (int i = 0; i < (int)this->roads.size(); i++) {
			this->roads[i]->draw(*this->window);
		}
		player->draw(*this->window);
		this->window->display();

		return true;
	}

	void addRoad(float x, float y) {
		this->roads.push_back(new Road(x, y));
	}

	virtual ~Level() {
		std::cout << "Level destructor\n";
		for (int i = 0; i < (int)this->roads.size(); i++) {
			delete this->roads[i];
		}
	}
};