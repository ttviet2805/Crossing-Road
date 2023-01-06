#pragma once
#include <SFML/Graphics.hpp>

#include "State.h"
#include "Rectangle.h"

class InstructionMenu :public State {
public:
	InstructionMenu() {
		this->initBackground(
			SCREEN_WIDTH, SCREEN_HEIGHT,
			"assets/image/Background/Instruction_fix.png"
		);
	}

	InstructionMenu(sf::RenderWindow* window) : State(SCREEN_WIDTH, SCREEN_HEIGHT, window) {
		this->initBackground(
			SCREEN_WIDTH, SCREEN_HEIGHT,
			"assets/image/Background/Instruction_fix.png"
		);
	}
	int run(Player* player) {
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return false;
			}
		}

		this->window->clear(sf::Color::Black);
		this->window->draw(this->loadSprite);
		this->window->display();

		return 8;
	}
};