#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
const int GAME_WIDTH = 1080;
const int GAME_HEIGHT = 768;

class Rectangle {
private:
	RectangleShape Rect;

public:
	// Rectangle has Size, Position and Image
	// Texture is image
	Rectangle() {}

	Rectangle(Vector2f _size, Vector2f _position, Texture& _texture) {
		Rect.setSize(_size);
		Rect.setPosition(_position);
		Rect.setTexture(&_texture);
	}

	~Rectangle() {}

	Rectangle& operator= (const Rectangle& src) {
		Rect = src.Rect;
		return *this;
	}

	// get Rectangle
	RectangleShape getRect() {
		return Rect;
	}

	// set image for Rectangle
	void setTexture(Texture& _texture) {
		Rect.setTexture(&_texture);
	}

	void setTexRect(IntRect& _texture) {
		Rect.setTextureRect(_texture);
	}

	void setSize(Vector2f _size) {
		Rect.setSize(_size);
	}

	void setPosition(Vector2f _position) {
		Rect.setPosition(_position);
	}

	Vector2f getPosition() {
		return Rect.getPosition();
	}

	Vector2f getSize() {
		return Rect.getSize();
	}

	// add x-axis position X
	// add y-axis position Y
	void move(float X, float Y) {
		Rect.move(X, Y);
	}

	// use this function to check move up, move down, move left, move right
	// this function don't return any thing

	// to check if mouse click or not
	// 0: not click
	// 1: left mouse click
	// 2: right mouse click
	int is_Clicked(Vector2f Position) {
		int isPress = 0;

		if (Rect.getGlobalBounds().contains(Position)) {
			while (Mouse::isButtonPressed(Mouse::Left)) isPress = 1;

			if (isPress == 1) return 1;

			return 2;
		}

		return 0;
	}

	// to check if 2 rectangle is collision or not
	bool isCollision(const Rectangle& X) {
		const bool collides = this->Rect.getGlobalBounds().intersects(X.Rect.getGlobalBounds());

		//if (collides) cout << "Collision\n";
		return collides;
	}
};