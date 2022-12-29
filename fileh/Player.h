#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Mediator.h"
#include "Rectangle.h"
#include <string>
class Player {
private:
	Point curPos;
	float curSpeed;
	sf::Texture character;
	sf::IntRect sourceRect;

	string imgPath;

	int face;

	Rectangle sprite;
	sf::Vector2u currentImage;
	sf::Vector2u imageCount;
	float totalTime, switchTime;

	float imgLength, imgHeight;

	//character info
	std::string name;
	int life;

	Mediator *mediator;

	sf::Clock clock;
public:
	
	/*Player() : curPos(Point()), curSpeed(10), totalTime(0), switchTime(0), face(0) { initCharacter(); }
	Player(double x, double y, double speed) : curPos(Point(x, y)), curSpeed(speed), face(0) { initCharacter(); }
	Player(const Player& src) : curPos(src.curPos), curSpeed(src.curSpeed), face(src.face) { initCharacter(); }*/

	Player(sf::Vector2u imageCount, float switchTime, Vector2f _Size, Vector2f _position, float imgLength = 64.0, float imgHeight = 128.0,
		string imgPath = "") :
		imageCount(imageCount), switchTime(switchTime), curSpeed(0.7f), face(0), imgLength(imgLength),
		imgHeight(imgHeight), imgPath(imgPath), life(1), name("")
	{
		this->totalTime = 0.f;
		this->currentImage.x = 0;

		initCharacter(_Size, _position); 
	}

	RectangleShape getRect() {
		return sprite.getRect();
	}

	Rectangle getSprite() {
		return this->sprite;
	}

	void draw(sf::RenderWindow& window) {
		this->curPos.checkRange(window);
		//this->sprite.setPosition(this->curPos.pos);
		window.draw(this->sprite.getRect());
	}

	void characterMove(float dentaTime, float limDown) {
		if (Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (sprite.getPosition().x - dentaTime > 0)
				sprite.move(-dentaTime, 0);
		}
		else {
			if (Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (sprite.getPosition().x + dentaTime + sprite.getSize().x < GAME_WIDTH)
					sprite.move(dentaTime, 0);
			}
			else {
				if (Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (sprite.getPosition().y - dentaTime > 0)
						sprite.move(0, -dentaTime);
				}
				else {
					if (Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						if (sprite.getPosition().y + dentaTime + sprite.getSize().y < limDown)
							sprite.move(0, dentaTime);
					}
				}
			}
		}
	}

	void updatePos(float limDown) {
		this->characterMove(this->curSpeed, limDown);
	}

	void setPos(float x, float y) {
		curPos.pos.x=x;
		curPos.pos.y=y;
		sprite.setPosition(curPos.pos);
	}

	void updateSprite(float deltaTime) {
		
		auto subDeltaTime = this->clock.restart().asSeconds();
		if (subDeltaTime > 1.0f / 60.0f) {
			subDeltaTime = 1.0f / 60.0f;
		}

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

	void initCharacter(Vector2f _Size, Vector2f _position) {
		this->character.loadFromFile(this->imgPath);
		this->sourceRect.width = this->character.getSize().x / (float)imageCount.x;
		this->sourceRect.height = this->character.getSize().y / (float)imageCount.y;
		this->sprite = Rectangle(_Size, _position, this->character);
	}

	void addMediator(Mediator* src) {
		this->mediator = src;
	}

	bool updateHeartText(int val) {
		this->life += val;
		std::string need = "";
		int heart = life;
		while (heart > 0) {
			need += ((heart % 10) + '0'); 
			heart /= 10;
		}
		reverse(need.begin(), need.end());
		if (need.empty()) need = "0";
		this->mediator->updateHeartText(need);

		return this->life < 0;
	}

	void changeSpeed(float speed);
	void updateInfo(std::string newName);

	virtual ~Player() {}
};