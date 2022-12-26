#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Rectangle.h"
#include "Road.h"
#include "Player.h"
#include "State.h"
#include "flag.h"
#include "PlayerMediator.h"

using namespace std;
using namespace sf;

const string ROADPATH = "assets/image/Road/Road";

const int ROADSIZE = 100;
const int DISTANCE = 1;

int Rand(int l, int r) {
	return l + (rand()) % (r - l + 1);
}

class Game : public State {
private:
	float deltaTime;
	//RenderWindow* window;
	Texture roadTexture[10];
	vector <Road*> lstRoad;
	View view;
	PlayerMediator *mediator;
	Texture flagTexture;
	Flag flag;
	
public:
	Game() : deltaTime(10) {}

	Game(RenderWindow* window, int difficulty, PlayerMediator *mediator) : State(SCREEN_WIDTH, SCREEN_HEIGHT, window), deltaTime(10), mediator(mediator) {
		int leftLimRoad, rightLimRoad, numPavement;
		if (difficulty == 1) leftLimRoad = 1, rightLimRoad = 3, numPavement = 10;
		if (difficulty == 2) leftLimRoad = 2, rightLimRoad = 4, numPavement = 15;
		if (difficulty == 3) leftLimRoad = 3, rightLimRoad = 5, numPavement = 20;

		srand(time(0));
		srand(static_cast <unsigned> (time(0)));
		view = View(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		for (int i = 0; i <= 6; i++) {
			string path = ROADPATH + to_string(i) + ".png";
			roadTexture[i].loadFromFile(path);
		}

		int cnt = 0;
		for (int i = 0; i < numPavement; i++) {
			Rectangle tmpRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
			Road* tmpRoad = new Road(tmpRect, 0);

			lstRoad.push_back(tmpRoad);

			int numRoad = Rand(leftLimRoad, rightLimRoad);
			int state = Rand(1, 7);
			int roadState = 1;

			if (state >= 5 && state <= 7) state = 5, roadState = 2;
			else
				if (state > 7) state = 6, roadState = 3;

			cnt++;

			for (int j = 0; j < numRoad; j++) {
				Rectangle otherRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[state]);
				Road* otherRoad = new Road(otherRect, roadState);

				lstRoad.push_back(otherRoad);

				this->mediator->addRoad(lstRoad[lstRoad.size() - 1]);
				cnt++;
			}
		}

		Rectangle tmpRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
		Road* tmpRoad = new Road(tmpRect, 0);

		lstRoad.push_back(tmpRoad);

		auto pos = tmpRoad->getRect().getPosition();
		flagTexture.loadFromFile("assets/Image/Object/Flag/Flag.png");
		flag = Rectangle(Vector2f(50, 50), Vector2f(pos.x + SCREEN_WIDTH / 2, pos.y + ROADSIZE / 2), flagTexture);
		//this->mediator->addRoad(&lstRoad);

		//cout << "Here\n";
	}

	int run(Player* player) {
		player->addMediator(this->mediator);
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
			lstRoad[i]->draw(*window);
		}	
		this->window->draw(this->flag.getRect());
			
		player->updatePos(0.4, lstRoad.size() * (ROADSIZE + DISTANCE));
		player->updateSprite(0.5);

		for (int i = 0; i < (int)this->lstRoad.size(); i++) {
			if (lstRoad[i]->startSearch(player->getSprite())) {
				cout << "Collision " << i << '\n';
			}
		}
		if (this->flag.collision(player->getSprite())) {
			view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
			window->setView(view);
			return 5;
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
		for (int i = 0; i < lstRoad.size(); i++)
			if (lstRoad[i]) {
				delete lstRoad[i];
			}

		lstRoad.clear();
		cout << "Game destructor\n";
	}

	friend class PlayerMediator;
};