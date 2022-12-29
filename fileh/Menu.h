#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Rectangle.h"

class Menu : public State {
private:
	sf::Texture texture[4];
	Rectangle button[4];

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
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 - 60), 
			this->texture[0]
		);

		this->texture[1].loadFromFile("assets/image/Button/Stats.png");
		this->button[1] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 + 40),
			this->texture[1]
		);

		this->texture[2].loadFromFile("assets/image/Button/Loadgame.png");
		this->button[2] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 + 140),
			this->texture[2]
		);

		this->texture[3].loadFromFile("assets/image/Button/Quit.png");
		this->button[3] = Rectangle(
			sf::Vector2f(266, 67),
			sf::Vector2f(SCREEN_WIDTH / 2 - 133, SCREEN_HEIGHT / 2 + 240),
			this->texture[3]
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

				if (this->button[2].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					
				}

				if (this->button[3].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 0;
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

	~Menu() {
		std::cout << "Menu destructor\n";
	}
};