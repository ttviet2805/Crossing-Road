#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Rectangle.h"

class Menu : public State {
private:
	sf::Texture texture;
	Rectangle startButton;

public:
	Menu() { this->setupButton(); }

	Menu(int x, int y, sf::RenderWindow* window) : State(x, y, window) { this->setupButton(); }

	void setupButton() {
		this->texture.loadFromFile("image/amogus.png");
		startButton = Rectangle(sf::Vector2f(200, 200), sf::Vector2f(500, 300), this->texture);
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
				if (this->startButton.is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
					return 2;
				}
			}
		}

		this->window->clear(sf::Color::Black);
		this->window->draw(this->startButton.getRect());
		this->window->display();

		return true;
	}

	~Menu() {
		std::cout << "Menu destructor\n";
	}
};