#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Rectangle.h"
#include "Road.h"
#include "Player.h"
#include "State.h"
#include "flag.h"
#include "PlayerMediator.h"
#include "PlayerStatus.h"

using namespace std;
using namespace sf;

const string ROADPATH = "assets/image/Road/Road";

const int ROADSIZE = 80;
const int DISTANCE = 1;

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

	// Game level management
	int* level;
	int leftLimRoad, rightLimRoad, numPavement;
	double objectSpeed;

	// Status
	Status playerStatus;
	
public:
	int randIntegerNumber(int l, int r) {
		return l + (rand()) % (r - l + 1);
	}

	Game() : deltaTime(10), level(nullptr) {}

	Game(RenderWindow* window, int* difficulty, PlayerMediator *mediator) : State(SCREEN_WIDTH, SCREEN_HEIGHT, window), deltaTime(10), mediator(mediator) {
		this->level = difficulty;
		cout << "Level: " << (*this->level) << '\n';

		const string LEVEL_PATH = "assets/Level/Level";
		string curPath = LEVEL_PATH + to_string(*level) + ".txt";
		
		ifstream fin(curPath);
		fin >> numPavement >> leftLimRoad >> rightLimRoad >> objectSpeed;
		fin.close();

		srand(time(0));
		srand(static_cast <unsigned> (time(0)));
		view = View(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		for (int i = 0; i <= 6; i++) {
			string path = ROADPATH + to_string(i) + ".png";
			roadTexture[i].loadFromFile(path);
		}

		int cnt = 0;
		for (int i = 0; i < numPavement; i++) {
			Rectangle tmpRect(Vector2f(GAME_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
			Road* tmpRoad = new Road(tmpRect, 0, objectSpeed, this->mediator);
			this->mediator->addRoad(tmpRoad);

			lstRoad.push_back(tmpRoad);

			int numRoad = randIntegerNumber(leftLimRoad, rightLimRoad);
			int state = randIntegerNumber(1, 7);
			int roadState = 1;

			if (state >= 5 && state <= 7) state = 5, roadState = 2;
			else
				if (state > 7) state = 6, roadState = 3;

			cnt++;

			for (int j = 0; j < numRoad; j++) {
				Rectangle otherRect(Vector2f(GAME_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[state]);
				Road* otherRoad = new Road(otherRect, roadState, objectSpeed, this->mediator);
				this->mediator->addRoad(otherRoad);
				lstRoad.push_back(otherRoad);

				//this->mediator->addRoad(lstRoad[lstRoad.size() - 1]);
				cnt++;
			}
		}

		Rectangle tmpRect(Vector2f(GAME_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
		Road* tmpRoad = new Road(tmpRect, 0, objectSpeed, this->mediator);
		this->mediator->addRoad(tmpRoad);
		lstRoad.push_back(tmpRoad);

		auto pos = tmpRoad->getRect().getPosition();
		flagTexture.loadFromFile("assets/Image/Object/Flag/Flag.png");
		flag = Rectangle(Vector2f(50, 50), Vector2f(pos.x + GAME_WIDTH / 2, pos.y + ROADSIZE / 2), flagTexture);
		this->mediator->addStatus(&this->playerStatus);
		
		//cout << "Here\n";
	}

	void setDifficulty() {
		
	}

	int run(Player* player) {
		player->addMediator(this->mediator);
		player->updateHeartText(0);
		this->updateLevelText();
		//player->addStatusTracker(&this->playerStatus);
		sf::Event event;
		while (this->window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
				window->setView(view);

				int viewPos = view.getCenter().y - view.getSize().y / 2;
				//cout << viewPos << endl;
				playerStatus.setPosition(viewPos);
				return 0;
			}
		}

		this->window->clear(Color::White);

		for (int i = 0; i < lstRoad.size(); i++) {
			lstRoad[i]->draw(*window);
		}	
		this->window->draw(this->flag.getRect());
		
		player->changeSpeed(-(*level) * 0.015f);
		player->updatePos(lstRoad.size() * (ROADSIZE + DISTANCE));
		player->changeSpeed((*level) * 0.015f);
		player->updateSprite(0.5);

		bool endGame = 0;

		for (int i = 0; i < (int)this->lstRoad.size(); i++) {
			int ans = lstRoad[i]->startSearch(player->getSprite());
			if (ans == 1) {
				this->mediator->updateLastPavement(i);
				
			}
			else if (ans == 2) {
				endGame = player->updateHeartText(-1);
				this->mediator->returnLastPos();
			}
		}
		if (this->flag.collision(player->getSprite())) {
			view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
			window->setView(view);
			(*this->level)++;
			return 5;
		}

		Vector2f characterPos = player->getRect().getPosition();
		characterPos.x = SCREEN_WIDTH / 2;
		characterPos.y = (characterPos.y > SCREEN_HEIGHT / 2) ? characterPos.y : SCREEN_HEIGHT / 2;
		if (characterPos.y + SCREEN_HEIGHT / 2 > lstRoad.size() * (ROADSIZE + DISTANCE))
			characterPos.y = lstRoad.size() * (ROADSIZE + DISTANCE) - SCREEN_HEIGHT / 2;
		view.setCenter(characterPos);
		window->setView(view);

		int viewPos = view.getCenter().y - view.getSize().y / 2;
		//cout << viewPos << endl;
		playerStatus.setPosition(viewPos);

		player->draw(*window);
		playerStatus.draw(*window);
		window->display();

		player->addMediator(nullptr);

		if (endGame) {
			view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
			window->setView(view);
			(*this->level) = 1;
			return 6;
		}

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

	void updateLevelText() {
		std::string add = "Level ";
		int cur = *this->level;
		std::string need = "";
		while (cur > 0) {
			need += ((cur % 10) + '0');
			cur /= 10;
		}
		reverse(need.begin(), need.end());
		if (need.empty()) need = "...";
		add += need;
		this->mediator->updateLevelText(add);
	}

	friend class PlayerMediator;
};