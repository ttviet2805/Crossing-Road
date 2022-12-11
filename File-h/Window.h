#pragma once
#include <iostream>
#include <vector>
#include <../SFML/Graphics.hpp>
#include "Road.h"
#include "Player.h"

class Window { 
private:
	int width, height;
	sf::RenderWindow* window;
	sf::RenderTexture backgroundImg;
	sf::Sprite loadSprite;
	sf::Texture texture;

	float deltaTime;

	std::vector<Road*> roads;

	sf::Clock clock;

	void initBackground(int x, int y);
public:

	Window();
	Window(int x, int y);

	void run(Player* player);
	void addRoad(float x, float y);
	
	virtual ~Window();
};