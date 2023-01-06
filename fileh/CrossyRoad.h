#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "../fileh/Level.h"
#include "../fileh/Player.h"
#include "../fileh/PlayerMediator.h"
#include "../fileh/Menu.h"
#include "../fileh/Game.h"
#include "../fileh/Rectangle.h"
#include "../fileh/WinMenu.h"
#include "../fileh/LoseMenu.h"
#include "../fileh/Save_Load.h"
#include "../fileh/Settings.h"
using namespace sf;

const string skinPath = "assets/Image/Skin/";
const string skinList[] = { "Skin1", "Skin2", "Skin3" };
const int imgCount[] = { 6, 6, 4 };
const pair<int, int> spriteSize[] = { {70, 98}, {70, 98} , {70, 98} };
const pair<int, int> imageSize[] = { {100, 140}, {100, 140}, {100, 140} };

void gameRun() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing Road");
	//Player player(Vector2u(10, 2), Vector2f(30, 65), Vector2f(0, 0), 3, 64, 120, "assets/image/human_walk_sprite.png");

	std::string path = skinPath + skinList[0];

	Player* player = new Player(6, Vector2f(70, 98), Vector2f(0, 0), 3, 100, 140, path);
	//player = Player(6, Vector2f(70, 98), Vector2f(0, 0), 3, 100, 140, path);

	vector<State*> nxt;
	nxt.push_back(new Menu(&window));

	PlayerMediator* playerMediator = new PlayerMediator(player);
	//player->addMediator(playerMediator);

	int difficulty = 1;

	const string MUSIC_PATH = "assets/Sound/Your-Smile.ogg";
	Music backgroundMusic;
	if (!backgroundMusic.openFromFile(MUSIC_PATH)) {
		cout << "Loading music error\n";
	}

	backgroundMusic.play();
	backgroundMusic.setLoop(true);

	const string MUSIC_LOSE_PATH = "assets/Sound/lose_game.ogg";
	Music loseMusic;
	if (!loseMusic.openFromFile(MUSIC_LOSE_PATH)) {
		cout << "Loading music error\n";
	}

	while (window.isOpen() && !nxt.empty()) {
		//std::cout << "here\n";
		int type = nxt.back()->run(player);

		switch (type) {
		case -1:
			nxt.push_back(new SettingsMenu(&window, &backgroundMusic));
			break;
		case 0:
			difficulty = 1;
			loseMusic.stop();
			backgroundMusic.stop();
			backgroundMusic.play();
			backgroundMusic.setLoop(true);
			delete nxt.back();
			nxt.pop_back();
			break;
		case 1:
			/*backgroundMusic.stop();
			backgroundMusic.play();
			backgroundMusic.setLoop(true);*/
			nxt.push_back(new Level(&window));
			break;
		case 2:
			/*backgroundMusic.stop();
			backgroundMusic.play();
			backgroundMusic.setLoop(true);*/
			player->setPos(SCREEN_WIDTH / 2.5, -30);
			//player.setlife(3);
			delete nxt.back();
			nxt.pop_back();
			playerMediator->clear();
			if (difficulty <= 7) {
				nxt.push_back(new Game(&window, &difficulty, playerMediator));
			}
			else {
				nxt.push_back(new WinMenu(&window, difficulty));
			}
			break;
		case 3:
			backgroundMusic.stop();
			backgroundMusic.play();
			backgroundMusic.setLoop(true);
			int heart;
			load_game(difficulty, heart);
			player->setlife(heart);
			player->setPos(SCREEN_WIDTH / 2.5, -30);
			//delete nxt.back();
			//nxt.pop_back();
			playerMediator->clear();
			nxt.push_back(new Game(&window, &difficulty, playerMediator));
			break;
			/*case 4:
				player.setPos(0, 0);
				delete nxt.back();
				nxt.pop_back();
				nxt.push_back(new Game(&window, 3, playerMediator));
				break;*/
		case 5:
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new WinMenu(&window, difficulty - 1));
			break;
		case 6:
			delete nxt.back();
			nxt.pop_back();
			backgroundMusic.stop();
			loseMusic.setVolume(100.f);
			loseMusic.play();
			nxt.push_back(new LoseMenu(&window));
			break;
		case 7:
			loseMusic.stop();
			backgroundMusic.stop();
			backgroundMusic.play();
			backgroundMusic.setLoop(true);
			player->setlife(3);
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Level(&window));
			break;
		case 8:
			break;
		default:
			std::string path = skinPath + skinList[type - 10];
			std::cout << path << '\n';

			//For some reasons this shit just doesn't work
			player = new Player(imgCount[type - 10], Vector2f(spriteSize[type - 10].first, spriteSize[type - 10].second),
				Vector2f(0, 0), 3, imageSize[type - 10].first, imageSize[type - 10].second, path);
			player->addMediator(playerMediator);
			player->setPos(SCREEN_WIDTH / 2.5, -30);
			playerMediator->clear();
			playerMediator->addPlayer(player);

			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, &difficulty, playerMediator));
			break;
		}
	}
	backgroundMusic.stop();
	delete player;
	delete playerMediator;
}