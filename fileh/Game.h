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
#include "AllTexture.h"

using namespace std;
using namespace sf;

const string ROADPATH = "assets/image/Road/Road";

const int ROADSIZE = 80;
const int DISTANCE = 1;

class Game : public State {
private:
	// Game level management
	int* level;
	int leftLimRoad, rightLimRoad, numPavement;
	double objectSpeed;
	float deltaTime;
	Clock gameClock;

	// Road
	Texture roadTexture[10];
	vector <Road*> lstRoad;

	// Status
	Status playerStatus;

	// Flag
	Texture flagTexture;
	Flag flag;

	// View and Mediator
	View view;
	PlayerMediator* mediator;

	// Game texture
	ListTexture* gameTexture;

public:
	int randIntegerNumber(int l, int r) {
		return l + (rand()) % (r - l + 1);
	}

	void saveScore() {
		vector <int> v;

		ifstream fin("assets/scoreboard.txt");

		int score;
		while (fin >> score) {
			v.push_back(score);
		}
		
		int curScore = int(gameClock.getElapsedTime().asSeconds());
		if (v[*level - 1] == 0) v[*level - 1] = curScore;
		v[*level - 1] = min(v[*level - 1], curScore);
	
		fin.close();

		while (v.size() < 7) v.push_back(0);

		ofstream fout("assets/scoreboard.txt");

		for (int i = 0; i < v.size(); i++) {
			fout << v[i] << '\n';
		}

		fout.close();
	}

	Game(RenderWindow* window, int* difficulty, PlayerMediator* mediator) : State(SCREEN_WIDTH, SCREEN_HEIGHT, window), deltaTime(10), mediator(mediator) {
		// Set up level for game
		this->level = difficulty;
		cout << "Level: " << (*this->level) << '\n';

		const string LEVEL_PATH = "assets/Level/Level";
		string curPath = LEVEL_PATH + to_string(*level) + ".txt";

		ifstream fin(curPath);
		fin >> numPavement >> leftLimRoad >> rightLimRoad >> objectSpeed;
		fin.close();

		// Set up View
		view = View(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

		// Initialize all texture for game
		gameTexture = new ListTexture();

		// Set up Road for game
		srand(time(0));
		srand(static_cast <unsigned> (time(0)));
		for (int i = 0; i <= 6; i++) {
			string path = ROADPATH + to_string(i) + ".png";
			roadTexture[i].loadFromFile(path);
		}

		int cnt = 0;
		for (int i = 0; i < numPavement; i++) {
			Rectangle tmpRect(Vector2f(GAME_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
			Road* tmpRoad = new Road(tmpRect, 0, objectSpeed, gameTexture, this->mediator);
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
				Road* otherRoad = new Road(otherRect, roadState, objectSpeed, gameTexture, this->mediator);
				this->mediator->addRoad(otherRoad);
				lstRoad.push_back(otherRoad);

				//this->mediator->addRoad(lstRoad[lstRoad.size() - 1]);
				cnt++;
			}
		}

		Rectangle lastRoadRect(Vector2f(GAME_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * cnt), roadTexture[0]);
		Road* lastRoad = new Road(lastRoadRect, 0, objectSpeed, gameTexture, this->mediator);
		this->mediator->addRoad(lastRoad);
		lstRoad.push_back(lastRoad);

		// Set Flag
		const int FLAG_SIZE = 65;
		auto pos = lastRoad->getRect().getPosition();
		flagTexture.loadFromFile("assets/Image/Object/Flag/Flag.png");
		flag = Rectangle(Vector2f(FLAG_SIZE, FLAG_SIZE), Vector2f(pos.x + GAME_WIDTH / 2, pos.y + 7), flagTexture);
		this->mediator->addStatus(&this->playerStatus);
		this->playerStatus.addMediator(this->mediator);

		this->mediator->changeSkin();

		gameClock.restart();
	}

	void setDifficulty() {

	}

	int run(Player* player) {

		player->addMediator(this->mediator);
		player->updateHeartText(0);
		player->updateSpeedText(0);
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

		//player->changeSpeed((*this->level - 1) * 0.075);

		bool checkNotBlock = true;
		for (int i = 0; i < (int)this->lstRoad.size(); i++) {
			bool ans = lstRoad[i]->searchRock(player->getNextSprite(lstRoad.size() * (ROADSIZE + DISTANCE)));
			if (ans) { checkNotBlock = false; break; }
		}

		player->updateSprite(0.5);
		//player->changeSpeed((*this->level - 1) * -0.075);

		bool endGame = 0;

		for (int i = 0; i < (int)this->lstRoad.size(); i++) {
			int itemType = lstRoad[i]->checkGetItem(player->getSprite());
			if (itemType == 1) {
				player->updateHeartText(1);
			}
			else if (itemType == 2) {
				player->updateSpeedText(1);
			}

			int ans = lstRoad[i]->startSearch(player->getSprite());
			if (ans == 1) {
				this->mediator->updateLastPavement(i);
			}
			else if (ans == 2) {
				endGame = player->updateHeartText(-1);
				this->mediator->returnLastPos();
			}
			else if (ans == 3) {
				checkNotBlock = false;
			}
		}
		if (this->flag.collision(player->getSprite())) {
			saveScore();
			view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
			window->setView(view);
			(*this->level)++;
			return 5;
		}

		if (checkNotBlock) {
			player->updatePos(lstRoad.size() * (ROADSIZE + DISTANCE));
		}

		Vector2f characterPos = player->getRect().getPosition();
		characterPos.x = SCREEN_WIDTH / 2;
		characterPos.y = (characterPos.y > SCREEN_HEIGHT / 2) ? characterPos.y : SCREEN_HEIGHT / 2;
		if (characterPos.y + SCREEN_HEIGHT / 2 > lstRoad.size() * (ROADSIZE + DISTANCE))
			characterPos.y = lstRoad.size() * (ROADSIZE + DISTANCE) - SCREEN_HEIGHT / 2;
		view.setCenter(characterPos);
		window->setView(view);

		int viewPos = view.getCenter().y - view.getSize().y / 2;
		playerStatus.setPosition(viewPos);

		player->draw(*window);
		playerStatus.draw(*window, event);
		window->display();

		player->addMediator(nullptr);

		if (endGame) {
			view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
			window->setView(view);
			(*this->level) = 1;
			return 6;
		}

		return 8;
	}

	~Game() {
		for (int i = 0; i < lstRoad.size(); i++)
			if (lstRoad[i]) {
				delete lstRoad[i];
			}

		lstRoad.clear();

		delete gameTexture;
		cout << "Game destructor\n";
	}

	void updateLevelText() {
		int cur = *this->level;
		string need = to_string(cur);
		this->mediator->updateLevelText(need);
	}

	friend class PlayerMediator;
};