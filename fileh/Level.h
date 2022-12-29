#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Road.h"
#include "Player.h"
#include "State.h"
#include "SelectCharacter.h"

class Level : public State {
private:
	int difficulty;

	float deltaSpeed;

	sf::Texture texture[4];
	Rectangle button[4];

	// Select character
	SelectChacracter curSelectCharacter;
public:

	Level() : State(0, 0, nullptr), difficulty(0), deltaSpeed(0) {

	}

	Level(sf::RenderWindow* window, float difficulty = 0, float deltaSpeed = 0) : 
	State(SCREEN_HEIGHT, SCREEN_WIDTH, window), difficulty(difficulty), deltaSpeed(deltaSpeed) 
	{
		this->initBackground(SCREEN_HEIGHT, SCREEN_WIDTH, "assets/image/Background/Menu-Background.jpg");
		this->setupButton();
	}

	void setupButton() {
		const int BUTTON_WIDTH = 322;
		const int BUTTON_HEIGHT = 100;

		this->texture[0].loadFromFile("assets/image/Button/Start.png");
		this->button[0] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(240 + 50, SCREEN_HEIGHT / 2 + 200),
			this->texture[0]
		);

		this->texture[3].loadFromFile("assets/image/Button/Cancel.png");
		this->button[3] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(480 + BUTTON_WIDTH - 50, SCREEN_HEIGHT / 2 + 200),
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
			}
		}

		this->window->clear(sf::Color::Black);
		this->window->draw(this->loadSprite);
	
		for (int i = 0; i < 4; i++) {
			this->window->draw(this->button[i].getRect());
		}

		curSelectCharacter.draw(*window);

		this->window->display();

		return 10;
	}

	void addRoad(float x, float y) {
		//this->roads.push_back(new Road(x, y));
	}

	virtual ~Level() { cout << "Level destructor\n"; }
};