#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Rectangle.h"
#include "PlayerStatus.h"
#include "State.h"

class WinMenu : public State {
private:
	bool finalScreen;

	sf::Texture texture[4];
	Rectangle button[2];

	Status* playerStatus;

	sf::Texture winningText;
	Rectangle winSprite;

public:
	WinMenu() : State(0, 0, nullptr) {

	}

	WinMenu(sf::RenderWindow* window, int level = 0) : State(SCREEN_WIDTH, SCREEN_HEIGHT, window) {
		//State(SCREEN_WIDTH, SCREEN_HEIGHT, window);
		if (level <= 7) {
			finalScreen = 0;
			string path = "assets/image/Background/SuperSaiyan";
			path += to_string(level);
			path += ".png";
			this->initBackground(700, 763, path);
			this->setPos(Vector2f(SCREEN_WIDTH / 2 - 700, 0));
			this->setupButton();
		}
		else {
			finalScreen = 1;
			string path = "assets/image/Background/DragonBalls.png";
			this->initBackground(SCREEN_WIDTH, SCREEN_HEIGHT, path);
			this->setPos(Vector2f(SCREEN_WIDTH / 2 - 500, 0));
			this->setupButton();

			this->winningText.loadFromFile("assets/image/Background/Winning.png");
			this->winSprite = Rectangle(sf::Vector2f(1050, 84), sf::Vector2f(200, SCREEN_HEIGHT / 2 + 50), this->winningText);
			//cout << "Winning\n";
		}
	}

	void setupButton() {
		const int BUTTON_WIDTH = 322;
		const int BUTTON_HEIGHT = 100;

		if (this->finalScreen) {
			this->texture[1].loadFromFile("assets/image/Button/Quit.png");
			this->button[1] = Rectangle(
				sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
				sf::Vector2f(SCREEN_WIDTH / 2 - BUTTON_WIDTH + 150, SCREEN_HEIGHT / 2 + 250),
				this->texture[1]
			);

			return;
		}

		this->texture[0].loadFromFile("assets/image/Button/NextLv.png");
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
					return 2;
				}
			}
		}

		this->window->clear();
		this->window->draw(this->loadSprite);
		if (this->finalScreen) this->window->draw(this->winSprite.getRect());
		for (int i = 0; i < 2; i++) {
			this->window->draw(this->button[i].getRect());
		}
		this->window->display();

		return 8;
	}

	virtual ~WinMenu() { std::cout << "WinGame destructor\n"; }
};
