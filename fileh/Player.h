#pragma once
#include <../SFML/Graphics.hpp>
#include "Point.h"

class Player {
private:
	Point curPos;
	float curSpeed;
	sf::Texture character;
	sf::IntRect sourceRect;

	int face;

	sf::RectangleShape sprite;
	sf::Vector2u currentImage;
	sf::Vector2u imageCount;
	float totalTime, switchTime;
public:

	
	Player() : curPos(Point()), curSpeed(10), totalTime(0), switchTime(0), face(0) { initCharacter(); }
	Player(double x, double y, double speed) : curPos(Point(x, y)), curSpeed(speed), face(0) { initCharacter(); }
	Player(const Player& src) : curPos(src.curPos), curSpeed(src.curSpeed), face(src.face) { initCharacter(); }

	Player(sf::Vector2u imageCount, float switchTime): imageCount(imageCount), switchTime(switchTime), curSpeed(3000.0f), face(0) {
		this->totalTime = 0.f;
		this->currentImage.x = 0;

		initCharacter(); 
	}

	void draw(sf::RenderWindow& window) {
		this->curPos.checkRange(window);
		this->sprite.setPosition(this->curPos.pos);
		window.draw(this->sprite);
	}

	void updatePos(sf::Event& event, float deltaTime) {
		sf::Vector2f movement;
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			this->face = 1;
			this->curPos.updatePoint(-this->curSpeed * deltaTime, 0);
			movement = sf::Vector2f(-this->curSpeed * deltaTime, 0);
			break;
		case sf::Keyboard::Right:
			this->face = 0;
			this->curPos.updatePoint(this->curSpeed * deltaTime, 0);
			movement = sf::Vector2f(this->curSpeed * deltaTime, 0);
			break;
		case sf::Keyboard::Up:
			this->curPos.updatePoint(0, -this->curSpeed * deltaTime);
			movement = sf::Vector2f(0, -this->curSpeed * deltaTime);
			break;
		case sf::Keyboard::Down:
			this->curPos.updatePoint(0, this->curSpeed * deltaTime);
			movement = sf::Vector2f(0, this->curSpeed * deltaTime);
			break;
		default:
			break;
		}

		this->sprite.move(movement);
	}

	void updateSprite(float deltaTime) {
		this->currentImage.y = this->face;
		this->totalTime += deltaTime;

		if (this->totalTime >= switchTime) {
			this->totalTime -= switchTime;
			this->currentImage.x++;

			if (this->currentImage.x >= this->imageCount.x) {
				this->currentImage.x = 1;
			}
		}

		this->sourceRect.left = this->currentImage.x * this->sourceRect.width;
		this->sourceRect.top = this->currentImage.y * this->sourceRect.height;

		this->sprite.setTextureRect(this->sourceRect);
	}

	void initCharacter() {
		this->character.loadFromFile("image/human_walk_sprite.png");
		this->sourceRect.width = this->character.getSize().x / (float)imageCount.x;
		this->sourceRect.height = this->character.getSize().y / (float)imageCount.y;
		this->sprite.setSize(sf::Vector2f(64, 128));
		this->curPos = Point(1300 / 2, 800 - 200);
		this->sprite.setPosition(sf::Vector2f(1300 / 2, 800 - 200));
		this->sprite.setTexture(&this->character);
	}

	virtual ~Player() {}
};