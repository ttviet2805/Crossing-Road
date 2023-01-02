#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Point.h"
#include "Mediator.h"
#include "Rectangle.h"

const std::string direction[] = { "Left", "Right", "Up", "Down" };

std::string getStr(int num);

class Player {
private:
	bool imgType;
	Point curPos;
	float curSpeed;
	string imgPath;
	int face;
	
	sf::Vector2u currentImage;
	sf::Vector2u imageCount;
	float totalTime, switchTime;
	float imgLength, imgHeight;

	//For a single frame
	sf::Texture character;
	sf::IntRect sourceRect;
	Rectangle sprite;

	//For many static image
	vector<sf::Texture> staticCharacter[4];
	vector<Rectangle> staticSprite[4];

	//character info
	std::string name;
	int life;

	Mediator *mediator;

	sf::Clock clock;
public:
	
	
	/*Player() : curPos(Point()), curSpeed(10), totalTime(0), switchTime(0), face(0) { initCharacter(); }
	Player(double x, double y, double speed) : curPos(Point(x, y)), curSpeed(speed), face(0) { initCharacter(); }
	Player(const Player& src) : curPos(src.curPos), curSpeed(src.curSpeed), face(src.face) { initCharacter(); }*/

	Player(sf::Vector2u imageCount, Vector2f _Size, Vector2f _position, int heart = 3, float imgLength = 64.0, float imgHeight = 128.0,
		string imgPath = "") :
		imageCount(imageCount), switchTime(0.1), curSpeed(0.6f), face(0), imgLength(imgLength),
		imgHeight(imgHeight), imgPath(imgPath), life(heart), name("")
	{
		this->imgType = 0;
		this->totalTime = 0.f;
		this->currentImage.x = 0;

		initCharacter(_Size, _position);
	}

	/*Player& operator=(const Player& src) {
		cout << "Cai chet cua cai chet\n";
		imgType = src.imgType; face = src.face;

		curPos = src.curPos; curSpeed = src.curSpeed;

		switchTime = src.switchTime; totalTime = src.totalTime;
		imgLength = src.imgLength; imgHeight = src.imgHeight;
		currentImage = src.currentImage; imageCount = src.imageCount;
		imgPath = src.imgPath;
		mediator = src.mediator;
		life = src.life; name = src.name;
		if (!this->imgType) {
			character = src.character;
			sourceRect = src.sourceRect;
			sprite = src.sprite;
		}
		else {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < src.imageCount.x; j++) {
					this->staticCharacter[i].push_back(src.staticCharacter[i][j]);
					this->staticSprite[i].push_back(src.staticSprite[i][j]);
				}
			}
		}

		return *this;
	}*/

	Player(int imagePerDir, Vector2f _Size, Vector2f _position, int heart = 3, float imgLength = 100.0, float imgHeight = 140.0,
		string imgPath = ""):
		switchTime(0.1), curSpeed(0.4f), face(0), imgLength(imgLength), 
		imgHeight(imgHeight), imgPath(imgPath), life(heart), name("")
	{
		this->imageCount.x = imagePerDir;
		this->imgType = 1;
		this->totalTime = 0.f;
		this->currentImage.x = 0;

		std::cout << "Cai chet" << '\n';

		initStaticCharacter(imagePerDir, _Size, _position);
	}

	string getStaticTexturePath() {
		return this->imgPath;
	}

	RectangleShape getRect() {
		if (!this->imgType) {
			return sprite.getRect();
		}
		else {
			return this->staticSprite[this->face][this->currentImage.x].getRect();
		}
	}

	Rectangle getSprite() {
		if (!this->imgType) {
			return this->sprite;
		}
		else {
			return this->staticSprite[this->face][this->currentImage.x];
		}
	}

	Rectangle getNextSprite(float limDown) {
		Rectangle cur = this->getSprite();
		if (Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (cur.getPosition().x - this->curSpeed > 0)
				cur.move(-this->curSpeed, 0);
		}
		else {
			if (Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (cur.getPosition().x + this->curSpeed + cur.getSize().x < GAME_WIDTH)
					cur.move(this->curSpeed, 0);
			}
			else {
				if (Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (cur.getPosition().y - this->curSpeed > 0)
						cur.move(0, -this->curSpeed);
				}
				else {
					if (Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						if (cur.getPosition().y + this->curSpeed + cur.getSize().y < limDown)
							cur.move(0, this->curSpeed);
					}
				}
			}
		}
		return cur;
	}

	void draw(sf::RenderWindow& window) {
		this->curPos.checkRange(window);
		//this->sprite.setPosition(this->curPos.pos);
		if (!this->imgType) {
			window.draw(this->sprite.getRect());
		}
		else {
			window.draw(this->staticSprite[this->face][this->currentImage.x].getRect());
		}
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

	void staticCharacterMove(float dentaTime, float limDown) {
		if (Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (int i = 0; i < this->imageCount.x; i++) {
				this->staticSprite[0][i].setPosition(
					this->staticSprite[this->face][currentImage.x].getPosition()
				);
			}
			if (this->staticSprite[0][currentImage.x].getPosition().x - dentaTime > 0)
				this->staticSprite[0][currentImage.x].move(-dentaTime, 0);
			this->face = 0;
		}
		else {
			
			if (Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				for (int i = 0; i < this->imageCount.x; i++) {
					this->staticSprite[1][i].setPosition(
						this->staticSprite[this->face][currentImage.x].getPosition()
					);
				}
				if (this->staticSprite[1][currentImage.x].getPosition().x + dentaTime + this->staticSprite[1][currentImage.x].getSize().x < GAME_WIDTH)
					this->staticSprite[1][currentImage.x].move(dentaTime, 0);
				this->face = 1;
			}
			else {
				if (Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					for (int i = 0; i < this->imageCount.x; i++) {
						this->staticSprite[2][i].setPosition(
							this->staticSprite[this->face][currentImage.x].getPosition()
						);
					}
					if (this->staticSprite[2][currentImage.x].getPosition().y - dentaTime > 0)
						this->staticSprite[2][currentImage.x].move(0, -dentaTime);
					this->face = 2;
				}
				else {
					if (Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						for (int i = 0; i < this->imageCount.x; i++) {
							this->staticSprite[3][i].setPosition(
								this->staticSprite[this->face][currentImage.x].getPosition()
							);
						}
						if (this->staticSprite[3][currentImage.x].getPosition().y + dentaTime + this->staticSprite[3][currentImage.x].getSize().y < limDown)
							this->staticSprite[3][currentImage.x].move(0, dentaTime);
						this->face = 3;
					}
				}
			}
		}
	}

	void updatePos(float limDown) {
		if (!this->imgType) {
			this->characterMove(this->curSpeed, limDown);
		}
		else {
			this->staticCharacterMove(this->curSpeed, limDown);
		}
		//cout << this->curSpeed << '\n';
	}

	void setPos(float x, float y) {
		curPos.pos.x=x;
		curPos.pos.y=y;
		if (!this->imgType) {
			this->sprite.setPosition(curPos.pos);
		}
		else {
			for (int i = 0; i < this->imageCount.x; i++) {
				this->staticSprite[this->face][i].setPosition(curPos.pos);
			}
		}
	}

	void updateStaticSprite(float deltaTime) {
		auto subDeltaTime = this->clock.restart().asSeconds();
		if (subDeltaTime > 1.0f / 60.0f) {
			subDeltaTime = 1.0f / 60.0f;
		}

	/*	if (Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->face = 0;
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->face = 1;
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->face = 2;
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			this->face = 3;
		}*/
		this->totalTime += subDeltaTime;

		if (this->totalTime >= switchTime) {
			this->totalTime -= switchTime;
			this->currentImage.x++;

			if (this->currentImage.x >= this->imageCount.x) {
				this->currentImage.x = 0;
			}
		}
	}

	void updateFrameSprite(float deltaTime) {
		if (!this->imgType) {
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
	}

	void updateSprite(float deltaTime) {
		if (!this->imgType) {
			this->updateFrameSprite(deltaTime);
		}
		else {
			this->updateStaticSprite(deltaTime);
		}
	}

	void initCharacter(Vector2f _Size, Vector2f _position) {
		this->character.loadFromFile(this->imgPath);
		this->sourceRect.width = this->character.getSize().x / (float)imageCount.x;
		this->sourceRect.height = this->character.getSize().y / (float)imageCount.y;
		this->sprite = Rectangle(_Size, _position, this->character);
	}

	void initStaticCharacter(int imagePerDir, Vector2f _Size, Vector2f _position) {
		for (int i = 0; i < 4; i++) {
			this->staticCharacter[i].resize(imagePerDir);
			this->staticSprite[i].resize(imagePerDir);
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < imagePerDir; j++) {
				std::string tmpImg = direction[i] + getStr(j);
				tmpImg += ".png";
				std::string path = this->imgPath + '/';
				path += tmpImg;
				this->staticCharacter[i][j].loadFromFile(path);
				this->staticSprite[i][j] = Rectangle(_Size, _position, this->staticCharacter[i][j]);
			}
		}	
	}

	void addMediator(Mediator* src) {
		this->mediator = src;
	}

	bool updateHeartText(int val) {
		this->life += val;
	
		this->mediator->updateHeartText(to_string(this->life));

		return this->life <= 0;
	}

	void updateSpeedText(int val) {
		const float ADD_SPEED = 0.05;
		this->curSpeed += ADD_SPEED * val;
		int addSpeed = this->curSpeed / ADD_SPEED;

		this->mediator->updateSpeedText(to_string(addSpeed));
	}
	void setlife(int heart) {
		life = heart;
	}
	void changeSpeed(float speed);
	void updateInfo(std::string newName);

	virtual ~Player() {}
};