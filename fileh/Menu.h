#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "State.h"
#include "Rectangle.h"

class Menu : public State {
private:
	sf::Texture texture[6];
	Rectangle button[6];

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

	bool isLoadFile() {
		int state = -1;
		ifstream fin("assets/save_game.txt");
		if (fin.eof()) return false;
		fin >> state;
		fin.close();
		
		if (state == -1) return false;
		return true;
	}

	void setupButton() {
		const int BUTTON_WIDTH = 322;
		const int BUTTON_HEIGHT = 100;

		this->texture[0].loadFromFile("assets/image/Button/Start.png");
		this->button[0] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(100, SCREEN_HEIGHT / 2 + 110),
			this->texture[0]
		);

		this->texture[1].loadFromFile("assets/image/Button/Load.png");
		this->button[1] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(200 + BUTTON_WIDTH, SCREEN_HEIGHT / 2 + 110),
			this->texture[1]
		);

		this->texture[2].loadFromFile("assets/image/Button/LeaderBoard.png");
		this->button[2] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(300 + 2 * BUTTON_WIDTH, SCREEN_HEIGHT / 2 + 110),
			this->texture[2]
		);

		this->texture[3].loadFromFile("assets/image/Button/Instruction.png");
		this->button[3] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(100, SCREEN_HEIGHT / 2 + 240),
			this->texture[3]
		);

		this->texture[4].loadFromFile("assets/image/Button/Setting.png");
		this->button[4] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(200 + BUTTON_WIDTH, SCREEN_HEIGHT / 2 + 240),
			this->texture[4]
		);

		this->texture[5].loadFromFile("assets/image/Button/Quit.png");
		this->button[5] = Rectangle(
			sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
			sf::Vector2f(300 + 2 * BUTTON_WIDTH, SCREEN_HEIGHT / 2 + 240),
			this->texture[5]
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
					if(isLoadFile()) return 3;
				}

				if (this->button[5].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 0;
				}

				if (this->button[4].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					cout << "Here\n";
					return -1;
				}

				if (this->button[3].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					cout << "Here\n";
					return -2;
				}

				if (this->button[2].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return -3;
				} 
			}
		}

		this->window->clear(sf::Color::Black);
		this->window->draw(this->loadSprite);
		for (int i = 0; i < 6; i++) {
			this->window->draw(this->button[i].getRect());
		}
		this->window->display();

		return 8;
	}

	~Menu() {
		std::cout << "Menu destructor\n";
	}
};