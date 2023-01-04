#include <SFML/Graphics.hpp>
#include "fileh/Rectangle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Settings");

    Texture curTexture;
    curTexture.loadFromFile("assets/Image/Background/BackgroundSettings.jpg");
    Rectangle backgroundRect(Vector2f(1080, 720), Vector2f(0, 0), curTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // window.draw(shape);
        window.draw(backgroundRect.getRect());
        window.display();
    }

    return 0;
}