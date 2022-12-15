#pragma once
#include <iostream>
#include <vector>
#include <../SFML/Graphics.hpp>
#include "Road.h"
#include "Player.h"
#include "State.h"

class Level : public State {
private:
	int difficulty;

	float deltaSpeed;

	sf::Texture texture[4];
	Rectangle button[4];
public:

	Level() : State(0, 0, nullptr), difficulty(0), deltaSpeed(0) {

	}

	Level(sf::RenderWindow* window, float difficulty = 0, float deltaSpeed = 0) : 
	State(SCREEN_HEIGHT, SCREEN_WIDTH, window), difficulty(difficulty), deltaSpeed(deltaSpeed) 
	{
		this->initBackground(SCREEN_HEIGHT, SCREEN_WIDTH, "assets/image/background_nay_con_chay_hon.jpg");
		this->setupButton();
	}

	void setupButton() {
		this->texture[0].loadFromFile("assets/image/Easy.png");
		this->button[0] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 - 100),
			this->texture[0]
		);

		this->texture[1].loadFromFile("assets/image/Medium.png");
		this->button[1] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2),
			this->texture[1]
		);

		this->texture[2].loadFromFile("assets/image/Hard.png");
		this->button[2] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 + 100),
			this->texture[2]
		);

		this->texture[3].loadFromFile("assets/image/Quit.png");
		this->button[3] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 + 200),
			this->texture[3]
		);
	}

	int run(Player* player) {

		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return 0;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				auto pos = sf::Mouse::getPosition(*this->window);
				if (this->button[3].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 0;
				}

				if (this->button[0].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 2;
				}

				if (this->button[1].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 3;
				}

				if (this->button[2].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 4;
				}
			}
		}

		this->window->clear(sf::Color::Black);
		this->window->draw(this->loadSprite);
		for (int i = 0; i < 4; i++) {
			this->window->draw(this->button[i].getRect());
		}
		this->window->display();

		return 10;
	}

	void addRoad(float x, float y) {
		//this->roads.push_back(new Road(x, y));
	}

	virtual ~Level() { cout << "Level destructor\n"; }
};