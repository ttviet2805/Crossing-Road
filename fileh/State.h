#pragma once
#include "Player.h"

class State {
private:

protected:
	int width, height;
	sf::RenderWindow* window;
	sf::RenderTexture backgroundImg;
	sf::Sprite loadSprite;
	sf::Texture texture;
public:
	State() : width(0), height(0), window(nullptr) {}

	State(int x, int y, sf::RenderWindow* window) : width(x), height(y), window(window) {}

	virtual int run(Player* player) = 0;
	virtual void loadWindow(sf::RenderWindow* window) {
		this->window = window;
	}

	virtual ~State() {}
};