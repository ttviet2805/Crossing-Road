#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Player.h"

int main()
{
    Player* player = new Player(sf::Vector2u(10, 2), 0.1f);

    Window game(1300, 800);
    game.run(player);

    delete player;
    return 0;
}