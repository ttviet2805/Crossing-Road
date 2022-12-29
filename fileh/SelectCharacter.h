#pragma once

#include <iostream>
#include "Rectangle.h"

class SelectChacracter {
private:
	Rectangle selectBackgroundRect;
	Texture selectBackgroundTexture;

	Rectangle leftButton;
	Texture leftTexture;
	Rectangle rightButton;
	Texture rightTexture;

	Rectangle characterSkin;
	Texture characterSkinTexture;

	int skinID = 1;
	int maxSkinID = 1;

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
	}
	void draw(sf::RenderWindow& window) {
		window.draw(selectBackgroundRect.getRect());
		window.draw(leftButton.getRect());
		window.draw(rightButton.getRect());
	}
};