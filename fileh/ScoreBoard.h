#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H

#include <fstream>
#include "State.h"
#include "ScoreCell.h"

class ScoreBoardMenu: public State {
private:
    ScoreCell cell[6];
    Texture textureCell;
public:
    ScoreBoardMenu() {}
    ScoreBoardMenu(sf::RenderWindow *window): State(SCREEN_WIDTH, SCREEN_HEIGHT, window) {
        this->initBackground(SCREEN_WIDTH, SCREEN_HEIGHT, "assets/image/Background/ScoreBoardBackground.jpeg");
        const int START=150, VERTICAL_DIST=60;
        sf::Vector2f POS[6];
        for(int i=0; i<3; ++i) {
            POS[i].x=0.5*(SCREEN_WIDTH/2-SCORE_CELL_WIDTH);
            POS[i].y=START+i*(VERTICAL_DIST+SCORE_CELL_HEIGHT);
        }

        for(int i=3; i<6; ++i) {
            POS[i].x=SCREEN_WIDTH/2+0.5*(SCREEN_WIDTH/2-SCORE_CELL_WIDTH);
            POS[i].y=POS[i-3].y;
        }

        ifstream fin("assets/scoreboard.txt");
        assert(fin);

        textureCell.loadFromFile("assets/image/road/Road6.png");

        int level, score, cnt=0;
        while(fin >> level >> score) {
            Rectangle background(sf::Vector2f(SCORE_CELL_WIDTH, SCORE_CELL_HEIGHT),
                                POS[cnt],
                                textureCell);
            cell[cnt]=ScoreCell(score, level, background);
            ++cnt;
        }

        fin.close();
    }

    int run(Player *player) {
        sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return false;
			}
		}

		this->window->clear(sf::Color::Black);
        this->window->draw(this->loadSprite);
        for(int i=0; i<6; ++i)
            cell[i].draw(window);
		this->window->display();

		return 8;
    }
};

#endif