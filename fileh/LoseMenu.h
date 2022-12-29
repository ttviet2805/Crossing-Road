#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "State.h"

class LoseMenu : public State {
private:
	sf::Texture texture[4];
	Rectangle button[2];

public:
	LoseMenu() : State(0, 0, nullptr) {

	}

	LoseMenu(sf::RenderWindow* window) : State(700, 763, window) {
		this->initBackground(700, 763, "assets/image/Background/Drip.jpg");
		this->setPos(Vector2f(SCREEN_WIDTH / 2 - 700, 0));
		this->setupButton();
	}

	void setupButton() {
		const int BUTTON_WIDTH = 322;
		const int BUTTON_HEIGHT = 100;

		this->texture[0].loadFromFile("assets/image/Button/Replay.png");
		this->button[0] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(SCREEN_WIDTH / 2 + (700 / 2 - BUTTON_WIDTH / 2), 763 / 2 - 80),
			this->texture[0]
		);

		this->texture[1].loadFromFile("assets/image/Button/Quit.png");
		this->button[1] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(SCREEN_WIDTH / 2 + (700 / 2 - BUTTON_WIDTH / 2), 763 / 2 + 80),
			this->texture[1]
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
				if (this->button[1].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 0;
				}

				if (this->button[0].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 7;
				}
			}
		}

		this->window->draw(this->loadSprite);
		for (int i = 0; i < 2; i++) {
			this->window->draw(this->button[i].getRect());
		}
		this->window->display();

		return 10;
	}

	virtual ~LoseMenu() { std::cout << "LoseGame destructor\n"; }
};
