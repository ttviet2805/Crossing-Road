#include <../SFML/Graphics.hpp>
#include "../fileh/Level.h"
#include "../fileh/Player.h"

#include "../fileh/Rectangle.h"

using namespace sf;

int main()
{
    Player* player = new Player(sf::Vector2u(10, 2), 0.1f);

    Level game(1080, 720);
    game.run(player);

    delete player;

    RenderWindow window(VideoMode(1080, 720), "My Window");

    //Texture character;
    //character.loadFromFile("image/Amongus.png");
    //Rectangle tmpRect(Vector2f(150, 200), Vector2f(200, 200), character);

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

    return 0;
}