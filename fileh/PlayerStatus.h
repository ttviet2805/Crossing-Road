#pragma once
#include <iostream>
#include "Rectangle.h"

class Status {
private:
	Rectangle rect;
	Texture statusTexture;
	Font font;
	Text levelText;

	Rectangle characterBackgroundRect;
	Texture characterBackgroundTexture;

	Rectangle characterSkin;
	Texture characterSkinTexture;

	Text groupText;

public:
	Status() {
		const string PATH = "assets/Image/PlayerStatus/Status.jpg";
		rect.setSize(Vector2f(SCREEN_WIDTH - GAME_WIDTH, SCREEN_HEIGHT + 5));
		rect.setPosition(Vector2f(GAME_WIDTH, 0));
		
		if (!statusTexture.loadFromFile(PATH)) {
			cout << "Loading status error\n";
		}
		rect.setTexture(statusTexture);

		const string FONT_PATH = "assets/Font/EvilEmpire-4BBVK.ttf";
		if (!font.loadFromFile(FONT_PATH)) {
			cout << "Loading font error\n";
		}

		levelText.setFont(font);
		levelText.setString("Level ...");
		levelText.setCharacterSize(50);
		levelText.setStyle(Text::Bold);

		groupText.setFont(font);
		groupText.setString("Group 8-CS202\nCrossing Road");
		groupText.setCharacterSize(40);
		groupText.setStyle(Text::Bold);

		const string CHARACTER_BACKGROUND_PATH = "assets/Image/PlayerStatus/Player-Background.png";
		if (!characterBackgroundTexture.loadFromFile(CHARACTER_BACKGROUND_PATH)) {
			cout << "Loading background error\n";
		}

		Vector2f rectPos = rect.getPosition();
		characterBackgroundRect.setPosition(Vector2f(rectPos.x + 10, rectPos.y + 250));
		characterBackgroundRect.setSize(Vector2f(266, 300));
		characterBackgroundRect.setTexture(characterBackgroundTexture);

		const string CHARACTER_SKIN_PATH = "assets/Image/Player/Songoku/Songoku.png";
		if (!characterSkinTexture.loadFromFile(CHARACTER_SKIN_PATH)) {
			cout << "Loading skin error\n";
		}

		Vector2f backgroundPos = characterBackgroundRect.getPosition();
		characterSkin.setPosition(Vector2f(backgroundPos.x + 33, backgroundPos.y + 35));
		characterSkin.setSize(Vector2f(200, 230));
		characterSkin.setTexture(characterSkinTexture);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(rect.getRect());

		const Vector2f statusPos = rect.getPosition();
		characterBackgroundRect.setPosition(Vector2f(statusPos.x + 10, statusPos.y + 250));
		window.draw(characterBackgroundRect.getRect());
		
		levelText.setPosition(Vector2f(statusPos.x + 65, statusPos.y + 30));
		window.draw(levelText);

		groupText.setPosition(Vector2f(statusPos.x + 25, statusPos.y + 660));
		window.draw(groupText);

		Vector2f backgroundPos = characterBackgroundRect.getPosition();
		characterSkin.setPosition(Vector2f(backgroundPos.x + 33, backgroundPos.y + 35));
		window.draw(characterSkin.getRect());
	}

	void setPosition(int posY) {
		Vector2f curPos = rect.getPosition();
		rect.setPosition(Vector2f(curPos.x, posY));
	}
};