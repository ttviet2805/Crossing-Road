#include <SFML/Graphics.hpp>
#include "fileh/Rectangle.h"

int main()
{
    const int BUTTON_WIDTH=256;
    const int BUTTON_HEIGHT=256;
    const int SCREEN_WIDTH=1080;
    const int SCREEN_HEIGHT=720;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Settings");

    Texture curTexture;
    curTexture.loadFromFile("assets/Image/Background/BackgroundSettings.jpg");
    Rectangle backgroundRect(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), Vector2f(0, 0), curTexture);

    Texture soundButton[2];
    Rectangle button[2];
    soundButton[0].loadFromFile("assets/Image/Button/soundOn.png");
    soundButton[1].loadFromFile("assets/Image/Button/soundOff.png");
    
    button[0]=Rectangle(
        sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
        sf::Vector2f(200, 200),
        soundButton[0]
    );
    button[1]=Rectangle(
        sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
        sf::Vector2f(300+BUTTON_WIDTH, 200),
        soundButton[1]
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(backgroundRect.getRect());
        for(int i=0; i<2; ++i)
            window.draw(button[i].getRect());
        window.display();
    }

    return 0;
}