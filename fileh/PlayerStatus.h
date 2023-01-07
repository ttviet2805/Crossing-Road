#pragma once
#include <iostream>
#include "Mediator.h"
#include "Rectangle.h"
#include "Save_Load.h"

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

	// Item
	Texture heartTexture;
	Rectangle heartRect;
	Text heartText;

	Texture speedTexture;
	Rectangle speedRect;
	Text speedText;

	// Save
	Texture saveTexture;
	Rectangle saveRect;

	// Level and Heart
	int level, heart;

	// Score
	int score = 10;
	Text scoreText;

	Mediator* mediator;
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

		const string CHARACTER_SKIN_PATH = "assets/Image/Skin/Skin1/Down0.png";
		if (!characterSkinTexture.loadFromFile(CHARACTER_SKIN_PATH)) {
			cout << "Loading skin error\n";
		}

		Vector2f backgroundPos = characterBackgroundRect.getPosition();
		characterSkin.setPosition(Vector2f(backgroundPos.x + 33, backgroundPos.y + 35));
		characterSkin.setSize(Vector2f(200, 230));
		characterSkin.setTexture(characterSkinTexture);

		// Heart
		const string HEART_PATH = "assets/Image/Item/Heart/Item0.jpg";
		if (!heartTexture.loadFromFile(HEART_PATH)) {
			cout << "Loading heart error\n";
		}
		heartRect.setPosition(Vector2f(rectPos.x + 50, rectPos.y + 120));
		heartRect.setSize(Vector2f(40, 40));
		heartRect.setTexture(heartTexture);

		heartText.setFont(font);
		heartText.setString(" : 2");
		heartText.setCharacterSize(40);
		heartText.setStyle(Text::Bold);

		// Speed
		const string SPEED_PATH = "assets/Image/Item/Speed/Item0.jpg";
		if (!speedTexture.loadFromFile(SPEED_PATH)) {
			cout << "Loading heart error\n";
		}
		speedRect.setPosition(Vector2f(rectPos.x + 50, rectPos.y + 180));
		speedRect.setSize(Vector2f(40, 40));
		speedRect.setTexture(speedTexture);

		speedText.setFont(font);
		speedText.setString(" : 2");
		speedText.setCharacterSize(40);
		speedText.setStyle(Text::Bold);

		// Save
		if (!saveTexture.loadFromFile("assets/Image/Button/Save.png")) {
			cout << "Loading save error\n";
		}

		Vector2f curPos = rect.getPosition();

		saveRect.setSize(Vector2f(180, 60));
		saveRect.setPosition(Vector2f(curPos.x + 55, curPos.y + 595));
		saveRect.setTexture(saveTexture);

		// Score
		scoreText.setFont(font);
		scoreText.setFillColor(Color::Green);
		scoreText.setString("Score: " + to_string(score));
		scoreText.setCharacterSize(35);
		scoreText.setStyle(Text::Bold);
		scoreText.setPosition(Vector2f(curPos.x + 60, curPos.y + 225));
	}

	void draw(sf::RenderWindow& window, Event& event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			auto pos = sf::Mouse::getPosition(window);
			if (saveRect.is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
				save_game(level, heart);
				cout << "Save file successful\n";
			}
		}
		

		window.draw(rect.getRect());

		const Vector2f statusPos = rect.getPosition();
		characterBackgroundRect.setPosition(Vector2f(statusPos.x + 10, statusPos.y + 280));
		window.draw(characterBackgroundRect.getRect());

		levelText.setPosition(Vector2f(statusPos.x + 65, statusPos.y + 30));
		window.draw(levelText);

		groupText.setPosition(Vector2f(statusPos.x + 25, statusPos.y + 660));
		window.draw(groupText);

		Vector2f backgroundPos = characterBackgroundRect.getPosition();
		characterSkin.setPosition(Vector2f(backgroundPos.x + 33, backgroundPos.y + 35));
		window.draw(characterSkin.getRect());


		// Heart draw
		heartRect.setPosition(Vector2f(statusPos.x + 50, statusPos.y + 120));
		window.draw(heartRect.getRect());
		heartText.setPosition(Vector2f(statusPos.x + 100, statusPos.y + 112));
		window.draw(heartText);

		// Speed draw
		speedRect.setPosition(Vector2f(statusPos.x + 50, statusPos.y + 180));
		window.draw(speedRect.getRect());
		speedText.setPosition(Vector2f(statusPos.x + 100, statusPos.y + 172));
		window.draw(speedText);

		// Save draw
		saveRect.setPosition(Vector2f(statusPos.x + 55, statusPos.y + 595));
		window.draw(saveRect.getRect());

		// Score draw
		scoreText.setPosition(Vector2f(statusPos.x + 60, statusPos.y + 225));
		window.draw(scoreText);
	}

	void setHeartString(std::string str) {
		heart = atoi(str.c_str());
		this->heartText.setString(": " + str);
	}

	void setSpeedString(std::string str) {
		this->speedText.setString(": " + str);
	}

	void setLevelString(std::string str) {
		level = atoi(str.c_str());
		this->levelText.setString("Level " + str);
	}

	void setPosition(int posY) {
		Vector2f curPos = rect.getPosition();
		rect.setPosition(Vector2f(curPos.x, posY));
	}

	void addMediator(Mediator* mediator) {
		this->mediator = mediator;
	}

	void changeTexture(string path) {
		//path += "/Down0.png";

		//cout << "Path: " << path << '\n';

		const string CHARACTER_SKIN_PATHS = path + "/Down0.png";
		if (!characterSkinTexture.loadFromFile(CHARACTER_SKIN_PATHS)) {
			cout << "Loading skin error\n";
		}

		Vector2f backgroundPos = characterBackgroundRect.getPosition();
		characterSkin.setPosition(Vector2f(backgroundPos.x + 33, backgroundPos.y + 35));
		characterSkin.setSize(Vector2f(200, 230));
		characterSkin.setTexture(characterSkinTexture);
	}
};