#ifndef SCORE_CELL_H
#define SCORE_CELL_H
#define SCORE_CELL_WIDTH 400
#define SCORE_CELL_HEIGHT 125
#include "Rectangle.h"
#include <assert.h>
#include <SFML/Graphics.hpp>

class ScoreCell {
private:
    int score;
    Rectangle cell;
    sf::Text content;
    sf::Font font;
public:
    ScoreCell() {}
    ScoreCell(int score, Rectangle background): score(score), cell(background) {
        assert(font.loadFromFile("assets/Font/EvilEmpire-4BBVK.ttf"));
    }
    void draw(sf::RenderWindow *window, std::string level) {
        window->draw(cell.getRect());

        content.setString(level + "\nScore: " + to_string(score));
        content.setCharacterSize(25);   
        content.setFillColor(sf::Color::Black);
        content.setFont(font);
        content.setStyle(sf::Text::Bold);

        sf::Vector2f pos=cell.getPosition();
        pos.x += 120;
        pos.y += 30;
        content.setPosition(pos);
        window->draw(content);
    }
};
#endif