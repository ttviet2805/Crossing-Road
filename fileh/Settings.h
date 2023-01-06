#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "State.h"
#include "Rectangle.h"

const int BUTTON_WIDTH = 256;
const int BUTTON_HEIGHT = 256;

class SettingsMenu: public State {
private:
	Texture soundButton[2];
	Rectangle button[2];

	sf::Music* backgroundMusic;

	int run(Player* player = nullptr);
public:

	SettingsMenu();

	SettingsMenu(sf::RenderWindow* window, sf::Music* backgroundMusic);
};