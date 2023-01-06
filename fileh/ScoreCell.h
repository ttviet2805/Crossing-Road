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
    int level;
    Rectangle cell;
    sf::Text content;
    sf::Font font;
public:
    ScoreCell() {}
    ScoreCell(int score, int level, Rectangle background): score(score), level(level), cell(background) {
        assert(font.loadFromFile("assets/Font/EvilEmpire-4BBVK.ttf"));
    }
    void draw(sf::RenderWindow *window) {
        window->draw(cell.getRect());

        content.setString("Level: " + to_string(level) + " - " + "Score: " + to_string(score));
        content.setCharacterSize(30);   
        content.setFillColor(sf::Color::White);
        content.setFont(font);
        content.setStyle(sf::Text::Bold);

        sf::Vector2f pos=cell.getPosition();
        pos.x += 50;
        pos.y += 50;
        content.setPosition(pos);
        window->draw(content);
    }
};
#endif