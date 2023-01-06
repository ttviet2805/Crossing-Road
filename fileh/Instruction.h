#pragma once
#include <SFML/Graphics.hpp>

#include "State.h"
#include "Rectangle.h"

class InstructionMenu :public State {
private:
	Rectangle quitRect;
	Texture quitTexture;
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

		if (!quitTexture.loadFromFile("assets/Image/Button/Quit.png")) {
			cout << "Loading quit error\n";
		}

		const Vector2f quitSize = Vector2f(240, 80);

		quitRect.setSize(quitSize);
		quitRect.setPosition(Vector2f((SCREEN_WIDTH - 240) / 2, SCREEN_HEIGHT - 90));
		quitRect.setTexture(quitTexture);
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
				if (quitRect.is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 0;
				}
			}
		}

		this->window->clear(sf::Color::Black);
		this->window->draw(this->loadSprite);
		this->window->draw(this->quitRect.getRect());

		this->window->display();

		return 8;
	}
};