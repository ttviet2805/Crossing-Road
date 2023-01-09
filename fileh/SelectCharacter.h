#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include "Rectangle.h"

const int WIDTH = 200;
const int HEIGHT = 280;

const int skinSize[] = { 0, 6, 6, 4 };
 
class SelectChacracter {
private:
	sf::RenderWindow* window;

	Rectangle selectBackgroundRect;
	Texture selectBackgroundTexture;

	Rectangle leftButton;
	Texture leftTexture;
	Rectangle rightButton;
	Texture rightTexture;

	int skinID = 1;
	const int maxSkinID = 3;

	Rectangle characterSkinRect;
	Texture characterSkinTexture[10];
	const float timeChangeFrame = 0.2;
	int curTexture = 0;
	//int maxTexture = 5;
	Clock clock;

public:
	SelectChacracter() {
		const string PATH = "assets/Image/Skin/Select-Character-Background.png";
		if (!selectBackgroundTexture.loadFromFile(PATH)) {
			cout << "Loading select background error\n";
		}

		const int BACKGROUND_WIDTH = 600;
		const int BACKGROUND_HEIGHT = 500;
		selectBackgroundRect.setSize(Vector2f(BACKGROUND_WIDTH, BACKGROUND_HEIGHT));
		selectBackgroundRect.setPosition(Vector2f((SCREEN_WIDTH - BACKGROUND_WIDTH) / 2, 50));
		selectBackgroundRect.setTexture(selectBackgroundTexture);

		Vector2f backgroundPos = selectBackgroundRect.getPosition();

		const string LEFT_BUTTON_PATH = "assets/Image/Skin/Left.png";
		if (!leftTexture.loadFromFile(LEFT_BUTTON_PATH)) {
			cout << "Loading left button error\n";
		}
		leftButton.setTexture(leftTexture);
		leftButton.setSize(Vector2f(50, 50));
		leftButton.setPosition(Vector2f(backgroundPos.x + 20, backgroundPos.y + BACKGROUND_HEIGHT / 2 - 20));

		const string RIGHT_BUTTON_PATH = "assets/Image/Skin/Right.png";
		if (!rightTexture.loadFromFile(RIGHT_BUTTON_PATH)) {
			cout << "Loading right button error\n";
		}
		rightButton.setTexture(rightTexture);
		rightButton.setSize(Vector2f(50, 50));
		rightButton.setPosition(Vector2f(backgroundPos.x + BACKGROUND_WIDTH - 20 - 50, backgroundPos.y + BACKGROUND_HEIGHT / 2 - 20));

		setSkinPotrait();

		characterSkinRect.setSize(Vector2f(WIDTH, HEIGHT));
		characterSkinRect.setPosition(Vector2f((SCREEN_WIDTH - WIDTH) / 2, backgroundPos.y + 125));
	}

	void setSkinPotrait() {
		for (int i = 0; i < skinSize[this->skinID]; i++) {
			string SKIN_PATH = "assets/Image/Skin/Skin" + to_string(this->skinID);
			SKIN_PATH += "/Down" + to_string(i) + ".png";
			if (!characterSkinTexture[i].loadFromFile(SKIN_PATH)) {
				cout << "Loading skin error\n";
			}
			characterSkinRect.setTexture(characterSkinTexture[0]);
		}
	}

	void addWindow(sf::RenderWindow* window) {
		this->window = window;
	}

	void draw(sf::RenderWindow& window) {
		if (Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto pos = sf::Mouse::getPosition(*this->window);
			if (this->leftButton.is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
				if (this->skinID > 1) this->skinID--;
			}

			if (this->rightButton.is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
				if (this->skinID < this->maxSkinID) this->skinID++;
			}

			setSkinPotrait();
		}

		window.draw(selectBackgroundRect.getRect());
		window.draw(leftButton.getRect());
		window.draw(rightButton.getRect());

		Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() >= timeChangeFrame) {
			curTexture = (curTexture + 1) % skinSize[this->skinID];
			characterSkinRect.setTexture(characterSkinTexture[curTexture]);
			clock.restart();
		}

		window.draw(characterSkinRect.getRect());
	}

	int getSkinID() {
		return this->skinID;
	}
};