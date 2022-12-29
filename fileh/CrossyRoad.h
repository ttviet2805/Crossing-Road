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
using namespace sf;

const string skinPath = "assets/Image/Skin/";
const string skinList[] = { "Skin1" };

void gameRun() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing Road");
	//Player player(Vector2u(10, 2), Vector2f(30, 65), Vector2f(0, 0), 3, 64, 120, "assets/image/human_walk_sprite.png");

	std::string path = skinPath + skinList[0];

	Player* player = new Player(6, Vector2f(70, 98), Vector2f(0, 0), 3, 100, 140, path);
	//player = Player(6, Vector2f(70, 98), Vector2f(0, 0), 3, 100, 140, path);

	vector<State*> nxt;
	nxt.push_back(new Menu(&window));

	PlayerMediator *playerMediator = new PlayerMediator(player);
	//player->addMediator(playerMediator);

	int difficulty = 1;

	const string MUSIC_PATH = "assets/Sound/Your-Smile.ogg";
	Music backgroundMusic;
	if (!backgroundMusic.openFromFile(MUSIC_PATH)) {
		cout << "Loading music error\n";
	}

	backgroundMusic.play();

	while (window.isOpen() && !nxt.empty()) {
		//std::cout << "here\n";
		int type = nxt.back()->run(player);

		switch (type) {
		case 0:
			delete nxt.back();
			nxt.pop_back();
			break;
		case 1:
			nxt.push_back(new Level(&window));
			break;
		case 2:
			player->setPos(0, 0);
			//player.setlife(3);
			delete nxt.back();
			nxt.pop_back();
			playerMediator->clear();
			nxt.push_back(new Game(&window, &difficulty, playerMediator));
			break;
		case 3:
			int level;
			int heart;
			load_game(level, heart);
			player->setlife(heart);
			player->setPos(0, 0);
			//delete nxt.back();
			//nxt.pop_back();
			playerMediator->clear();
			nxt.push_back(new Game(&window, &level, playerMediator));
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
			nxt.push_back(new WinMenu(&window));
			break;
		case 6:
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new LoseMenu(&window));
			break;
		case 7:
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
			player = new Player(6, Vector2f(70, 98), Vector2f(0, 0), 3, 100, 140, path);
			player->addMediator(playerMediator);
			player->setPos(0, 0);
			playerMediator->clear();
			playerMediator->addPlayer(player);

			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, &difficulty, playerMediator));
			break;
		}
	}

	delete player;
	delete playerMediator;
}