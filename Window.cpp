#include "Window.h"

Window::Window(): height(0), width(0), window(nullptr), deltaTime(0) {
    
}

void Window::initBackground(int x, int y) {
    if (!this->backgroundImg.create(x, y)) {
        //lol
    }

    if (!this->texture.loadFromFile("image/background.jpg")) {
        std::cout << "Dumb fuck\n";
    }
    this->addRoad(0, 100); this->addRoad(0, 300); this->addRoad(0, 500);
    this->loadSprite = sf::Sprite(this->texture);
    this->backgroundImg.draw(this->loadSprite);
}

Window::Window(int x, int y): width(x), height(y), window(nullptr), deltaTime(0) {
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Crossy Road");
    this->initBackground(x, y);
}

Window::~Window() {
	delete this->window;
    for (int i = 0; i < (int)this->roads.size(); i++) {
        delete this->roads[i];
    }
}

void Window::addRoad(float x, float y) {
    this->roads.push_back(new Road(x, y));
}

void Window::run(Player* player) {
    while (this->window->isOpen())
    {
        this->deltaTime = this->clock.restart().asSeconds();
        if (deltaTime > 1.0f / 60.0f) {
            deltaTime = 1.0f / 60.0f;
        }

        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window->close();
            if (event.type == sf::Event::KeyPressed) {
                player->updatePos(event, this->deltaTime);
            }
        }

        player->updateSprite(deltaTime);

        this->window->clear(sf::Color::Black);
        this->window->draw(this->loadSprite);
        for (int i = 0; i < (int)this->roads.size(); i++) {
            this->roads[i]->draw(*this->window);
        }
        player->draw(*this->window);
        this->window->display();
    }
}