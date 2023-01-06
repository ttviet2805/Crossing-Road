#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "../fileh/Settings.h"

SettingsMenu::SettingsMenu() : State(0, 0, nullptr) {

}

SettingsMenu::SettingsMenu(sf::RenderWindow* window, sf::Music* backgroundMusic): State(SCREEN_WIDTH, SCREEN_HEIGHT, window) {
	this->backgroundMusic = backgroundMusic;
	this->initBackground(SCREEN_WIDTH, SCREEN_HEIGHT, "assets/Image/Background/BackgroundSettings.png");

	this->soundButton[0].loadFromFile("assets/Image/Button/soundOn.png");
	this->soundButton[1].loadFromFile("assets/Image/Button/soundOff.png");

	this->button[0] = Rectangle(
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(SCREEN_WIDTH / 2 - 50 - BUTTON_WIDTH, SCREEN_HEIGHT / 2 - 100),
		this->soundButton[0]
	);
	this->button[1] = Rectangle(
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 100),
		this->soundButton[1]
	);

	if (!this->backgroundMusic->openFromFile("assets/Sound/Your-Smile.ogg")) {
		std::cerr << "Error: can't open music!" << std::endl;
		exit(2);
	}
	if (!quitTexture.loadFromFile("assets/Image/Button/Quit.png")) {
		cout << "Loading quit error\n";
	}

	const Vector2f quitSize = Vector2f(240, 80);

	quitRect.setSize(quitSize);
	quitRect.setPosition(Vector2f((SCREEN_WIDTH - 240) / 2, SCREEN_HEIGHT - 125));
	quitRect.setTexture(quitTexture);
	this->backgroundMusic->play();
	this->backgroundMusic->setLoop(true);
}

int SettingsMenu::run(Player* player) {
	sf::Event event;
	while (this->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			backgroundMusic->stop();
			return 0;

		}
		if (event.type == sf::Event::MouseButtonPressed) {
			auto pos = sf::Mouse::getPosition(*this->window);
			if (this->button[0].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
				// turn on the sound
				this->backgroundMusic->setVolume(80);

			}
			if (button[1].is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
				// turn off the sound
				this->backgroundMusic->setVolume(0);
			}
			if (quitRect.is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
				return 0;
			}
		}
	}

	this->window->clear(sf::Color::Black);
	this->window->draw(this->loadSprite);
	for (int i = 0; i < 2; ++i)
		window->draw(button[i].getRect());
	this->window->draw(this->quitRect.getRect());
	window->display();
	return 8;
}
// backgroundMusic.stop();