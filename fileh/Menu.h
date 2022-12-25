#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Rectangle.h"

class Menu : public State {
private:
	sf::Texture texture[2];
	Rectangle button[2];

public:
	Menu() {
		this->setupButton(); this->initBackground(
			SCREEN_WIDTH, SCREEN_HEIGHT,
			"assets/image/Background/Game-Background.jpg"
		);
	}

	Menu(sf::RenderWindow* window) : State(SCREEN_WIDTH, SCREEN_HEIGHT, window) {
		this->setupButton(); this->initBackground(
			SCREEN_WIDTH, SCREEN_HEIGHT,
			"assets/image/Background/Game-Background.jpg"
		);
	}

	void setupButton() {
		this->texture[0].loadFromFile("assets/image/Button/Start.png");
		this->button[0] = Rectangle(
			sf::Vector2f(266, 67), 
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 + 75), 
			this->texture[0]
		);

		this->texture[1].loadFromFile("assets/image/Button/Quit.png");
		this->button[1] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 + 170),
			this->texture[1]
		);
	}

	int run(Player* player) {
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return false;
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				auto pos = sf::Mouse::getPosition(*this->window);
				if (this->button[0].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 1;
				}

				if (this->button[1].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 0;
				}
			}
		}

		this->window->clear(sf::Color::Black);
		this->window->draw(this->loadSprite);
		for (int i = 0; i < 2; i++) {
			this->window->draw(this->button[i].getRect());
		}
		this->window->display();

		return 10;
	}

	~Menu() {
		std::cout << "Menu destructor\n";
	}
};