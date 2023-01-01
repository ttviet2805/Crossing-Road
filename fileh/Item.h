#pragma once

#include <iostream>
#include "Rectangle.h"

class Item {
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
};

