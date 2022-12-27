#pragma once
#include <SFML/Graphics.hpp>
#include "../fileh/Level.h"
#include "../fileh/Player.h"
#include "../fileh/PlayerMediator.h"
#include "../fileh/Menu.h"
#include "../fileh/Game.h"
#include "../fileh/Rectangle.h"
#include "../fileh/WinMenu.h"

using namespace sf;

void gameRun() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing Road");
	Player player(Vector2u(10, 2), 0.1, Vector2f(40, 80), Vector2f(0, 0), 64, 120, "assets/image/human_walk_sprite.png");

	vector<State*> nxt;
	nxt.push_back(new Menu(&window));

	PlayerMediator *playerMediator = new PlayerMediator(&player);
	player.addMediator(playerMediator);

	int difficulty = 1;

	while (window.isOpen() && !nxt.empty()) {
		//std::cout << "here\n";
		int type = nxt.back()->run(&player);

		switch (type) {
		case 0:
			delete nxt.back();
			nxt.pop_back();
			break;
		case 1:
			nxt.push_back(new Level(&window));
			break;
		case 2:
			player.setPos(0, 0);
			delete nxt.back();
			nxt.pop_back();
			playerMediator->clear();
			nxt.push_back(new Game(&window, &difficulty, playerMediator));
			break;
		/*case 3:
			player.setPos(0, 0);
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, 2, playerMediator));
			break;*/
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
			nxt.push_back(new Level(&window));
			break;
		default:
			break;
		}
	}
}