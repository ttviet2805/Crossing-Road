#include <SFML/Graphics.hpp>
#include "../fileh/Level.h"
#include "../fileh/Player.h"
#include "../fileh/Menu.h"
#include "../fileh/Game.h"

#include "../fileh/Rectangle.h"
using namespace sf;

void gameRun() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing Road");
	Player player(Vector2u(10, 2), 0.1, Vector2f(40, 80), Vector2f(0, 0), 64, 120, "assets/image/human_walk_sprite.png");

	vector<State*> nxt;
	nxt.push_back(new Menu(&window));

	PlayerMediator *playerMediator=new PlayerMediator(&player);
	player.addMediator(playerMediator);

	//Level game(1080, 720);
	//game.run(player);
	while (window.isOpen() && !nxt.empty()) {
		//std::cout << "Here\n";
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
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, 1, playerMediator));
			break;
		case 3:
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, 2, playerMediator));
			break;
		case 4:
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, 3, playerMediator));
			break;
		default:
			break;
		}
	}
}