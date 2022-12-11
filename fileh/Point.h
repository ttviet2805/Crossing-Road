#pragma once
#include <iostream>
#include <../SFML/Graphics.hpp>

class Point {
public:
	sf::Vector2f pos;

	Point() { pos = sf::Vector2f(0.f, 0.f); };
	Point(double x, double y) { pos = sf::Vector2f(x, y); };
	Point(const Point& src): pos(src.pos) {};
	Point& operator=(const Point& src){
		if(this == &src) return *this;
		pos.x = src.pos.x;
		pos.y = src.pos.y;
		return *this;
	}
	void updatePoint(double x, double y) {
		this->pos.x += x;
		this->pos.y += y; 
		//std::cout << pos.x << ' ' << pos.y << '\n';
	}

	void checkRange(sf::RenderWindow& window) {
		auto siz = window.getSize();
		if (this->pos.x < 0) this->pos.x = 0;
		if (this->pos.x > siz.x) this->pos.x = siz.x;
		if (this->pos.y < 0) this->pos.y = 0;
		if (this->pos.y > siz.y) this->pos.y = siz.y;
	}

	virtual ~Point() {};
};
