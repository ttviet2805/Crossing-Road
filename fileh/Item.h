#pragma once

#include <iostream>
#include "Rectangle.h"
#include "Object_static.h"

class Item: public Object_static {
private:
	Rectangle rect;

	// = 0 if heart
	// = 1 if speed
	int itemState;

public:
	Item(Rectangle _rect, int _itemState) {
		rect = _rect;
		itemState = _itemState;
	}

	void draw(RenderWindow& window) {
		window.draw(rect.getRect());
	}

	bool collision(Rectangle src) {
		Vector2f srcPoint = src.getPosition();
		Vector2f thisPoint = (this->rect).getPosition();
		if ((this->rect).isCollision(src) && srcPoint.y <= thisPoint.y) return true;
		else return false;
	}

	Rectangle getrect() {
		return rect;
	}

	RectangleShape getRect() {
		return rect.getRect();
	}
};

