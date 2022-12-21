#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "fileh/Rectangle.h"
#include "fileh/Road.h"
#include "fileh/Player.h"
#include "fileh/State.h"
#include "fileh/PlayerMediator.h"
using namespace std;
using namespace sf;

const string ROADPATH = "assets/image/Road/Road";

const int ROADSIZE = 100;
const int DISTANCE = 3;

int Rand(int l, int r) {
	return l + (rand()) % (r - l + 1);
}

class Game : public State {
private:
	float deltaTime;
	//RenderWindow* window;
	Texture roadTexture[5];
	vector <Road> lstRoad;
	View view;
	Clock clock[10005];
	Texture flagTexture;
	Rectangle flagRect;
	PlayerMediator mediator;
	
public:
	Game() : deltaTime(10) {}

	Game(RenderWindow* window, int difficulty) : State(SCREEN_WIDTH, SCREEN_HEIGHT, window), deltaTime(10) {
		int leftLimRoad, rightLimRoad, numPavement;
		if (difficulty == 1) leftLimRoad = 1, rightLimRoad = 3, numPavement = 10;
		if (difficulty == 2) leftLimRoad = 2, rightLimRoad = 4, numPavement = 15;
		if (difficulty == 3) leftLimRoad = 3, rightLimRoad = 5, numPavement = 20;

		mediator = PlayerMediator();

		srand(time(0));
		srand(static_cast <unsigned> (time(0)));
		view = View(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		for (int i = 0; i < 5; i++) {
			string path = ROADPATH + to_string(i) + ".png";
			roadTexture[i].loadFromFile(path);
		}

		int cnt = 0;
		for (int i = 0; i < numPavement; i++) {
			Rectangle tmpRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
			Road tmpRoad(tmpRect, false);

			lstRoad.push_back(tmpRoad);

			int numRoad = Rand(leftLimRoad, rightLimRoad);
			int state = Rand(1, 4);
			cnt++;

			for (int j = 0; j < numRoad; j++) {
				Rectangle otherRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[state]);
				Road otherRoad(otherRect, true);

				lstRoad.push_back(otherRoad);
				mediator.addRoad(&lstRoad[lstRoad.size() - 1]);
				cnt++;
			}
		}

		Rectangle tmpRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
		Road tmpRoad(tmpRect, false);

		lstRoad.push_back(tmpRoad);

		flagTexture.loadFromFile("assets/image/Flag.png");
		Rectangle tmpFlag(Vector2f(90, 90), Vector2f((SCREEN_WIDTH - 90) / 2, (ROADSIZE + DISTANCE) * cnt + 5), flagTexture);
		flagRect = tmpFlag;
	}

	int run(Player* player) {
		player->addMediator(&this->mediator);
		sf::Event event;
		while (this->window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
				window->setView(view);
				return 0;
			}
		}

		this->window->clear(Color::White);

		for (int i = 0; i < lstRoad.size(); i++) {
			lstRoad[i].draw(*window, clock[i]);
		}	

		window->draw(flagRect.getRect());
			
		player->updatePos(0.5, lstRoad.size() * (ROADSIZE + DISTANCE));
		player->updateSprite(0.5);

		for (int i = 0; i < (int)this->lstRoad.size(); i++) {
			if (lstRoad[i].startSearch(player->getSprite())) {
				cout << "Collision " << i << '\n';
			}
		}

		Vector2f characterPos = player->getRect().getPosition();
		characterPos.x = SCREEN_WIDTH / 2;
		characterPos.y = (characterPos.y > SCREEN_HEIGHT / 2) ? characterPos.y : SCREEN_HEIGHT / 2;
		if (characterPos.y + SCREEN_HEIGHT / 2 > lstRoad.size() * (ROADSIZE + DISTANCE))
			characterPos.y = lstRoad.size() * (ROADSIZE + DISTANCE) - SCREEN_HEIGHT / 2;
		view.setCenter(characterPos);
		window->setView(view);

		player->draw(*window);
		window->display();

		player->addMediator(nullptr);
		return 10;
	}

	~Game() {
		cout << "Game destructor\n";
	}
};