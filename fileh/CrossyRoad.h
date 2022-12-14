#include <../SFML/Graphics.hpp>
#include "../fileh/Level.h"
#include "../fileh/Player.h"
#include "../fileh/Menu.h"
#include "../fileh/Game.h"

#include "../fileh/Rectangle.h"
using namespace sf;

void gameRun() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing Road");
	Player player(Vector2u(10, 2), 0.1, Vector2f(64, 120), Vector2f(0, 0), 64, 120, "image/human_walk_sprite.png");

	vector<State*> nxt;
	nxt.push_back(new Menu(&window));

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
			nxt.push_back(new Game(&window, 1));
			break;
		case 3:
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, 2));
			break;
		case 4:
			delete nxt.back();
			nxt.pop_back();
			nxt.push_back(new Game(&window, 3));
			break;
		default:
			break;
		}
	}

	/*Texture character;
	character.loadFromFile("image/Amongus.png");
	Rectangle tmpRect(Vector2f(150, 200), Vector2f(200, 200), character);

	Rectangle c = tmpRect;*/

	//Texture newCharacter;
	//newCharacter.loadFromFile("image/Songoku.png");
	//Rectangle newRect(Vector2f(150, 200), Vector2f(600, 600), newCharacter);


	/*while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::White);

		window.draw(tmpRect.getRect());
		window.draw(newRect.getRect());

		tmpRect.characterMove(1);

		tmpRect.isCollision(newRect);


		window.display();
	}*/
}