#pragma once
#include <../SFML/Graphics.hpp>
#include "Point.h"
#include "PlayerObserver.h"
#include "Rectangle.h"
#include <string>
class Player {
private:
	Point curPos;
	float curSpeed;
	sf::Texture character;
	sf::IntRect sourceRect;

	int face;

	Rectangle sprite;
	sf::Vector2u currentImage;
	sf::Vector2u imageCount;
	float totalTime, switchTime;

	float imgLength, imgHeight;
	std::string name;
	PlayerObserver *observer;
public:
	
	/*Player() : curPos(Point()), curSpeed(10), totalTime(0), switchTime(0), face(0) { initCharacter(); }
	Player(double x, double y, double speed) : curPos(Point(x, y)), curSpeed(speed), face(0) { initCharacter(); }
	Player(const Player& src) : curPos(src.curPos), curSpeed(src.curSpeed), face(src.face) { initCharacter(); }*/

	Player(sf::Vector2u imageCount, float switchTime, float imgLength = 64.0, float imgHeight = 128.0): 
	imageCount(imageCount), switchTime(switchTime), curSpeed(3000.0f), face(0), imgLength(imgLength),
	imgHeight(imgHeight) 
	{
		this->totalTime = 0.f;
		this->currentImage.x = 0;

		initCharacter(); 
	}

	void draw(sf::RenderWindow& window) {
		this->curPos.checkRange(window);
		//this->sprite.setPosition(this->curPos.pos);
		window.draw(this->sprite.getRect());
	}

	void updatePos(sf::Event& event, float deltaTime) {
		//std::cout << "Key pressed\n";
		this->sprite.characterMove(deltaTime);
	}

	void updateSprite(float deltaTime) {
		
		auto subDeltaTime = 0.025f;

		this->currentImage.y = this->face;

		if (Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->face = 1;
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->face = 0;
		}
 		this->totalTime += subDeltaTime;

		if (this->totalTime >= switchTime) {
			this->totalTime -= switchTime;
			this->currentImage.x++;

			if (this->currentImage.x >= this->imageCount.x) {
				this->currentImage.x = 1;
			}
		}

		this->sourceRect.left = this->currentImage.x * this->sourceRect.width;
		this->sourceRect.top = this->currentImage.y * this->sourceRect.height;

		this->sprite.setTexRect(this->sourceRect);
	}

	void initCharacter() {
		this->character.loadFromFile("image/human_walk_sprite.png");
		this->sourceRect.width = this->character.getSize().x / (float)imageCount.x;
		this->sourceRect.height = this->character.getSize().y / (float)imageCount.y;
		this->sprite = Rectangle(sf::Vector2f(this->imgLength, this->imgHeight), sf::Vector2f(1280 / 2, 720 - 200), this->character);
	}

	void changeSpeed(float speed);
	void move(int direction);
	void updateInfo(std::string newName);

	virtual ~Player() {}
};