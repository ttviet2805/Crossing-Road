#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H

#include <fstream>
#include "State.h"
#include "ScoreCell.h"

class ScoreBoardMenu: public State {
private:
    ScoreCell cell[7];
    Texture textureCell;
    Rectangle quitRect;
    Texture quitTexture;
public:
    ScoreBoardMenu() {}
    ScoreBoardMenu(sf::RenderWindow *window): State(SCREEN_WIDTH, SCREEN_HEIGHT, window) {
        this->initBackground(SCREEN_WIDTH, SCREEN_HEIGHT, "assets/Image/Background/ScoreBoardBackground.jpg");
        const int START=100, VERTICAL_DIST=20;
        sf::Vector2f POS[7];
        for(int i=0; i<3; ++i) {
            POS[i].x=0.5*(SCREEN_WIDTH/2-SCORE_CELL_WIDTH);
            POS[i].y=START+i*(VERTICAL_DIST+SCORE_CELL_HEIGHT);
        }

        for(int i=3; i<6; ++i) {
            POS[i].x=SCREEN_WIDTH/2+0.5*(SCREEN_WIDTH/2-SCORE_CELL_WIDTH);
            POS[i].y=POS[i-3].y;
        }

        POS[6].x = 0.5 * (SCREEN_WIDTH - SCORE_CELL_WIDTH);
        POS[6].y = POS[5].y + SCORE_CELL_HEIGHT - 10;

        ifstream fin("assets/scoreboard.txt");
        assert(fin);

        textureCell.loadFromFile("assets/Image/Background/ScoreCell.png");

        int score, cnt = 0;
        while(fin >> score) {
            Rectangle background(sf::Vector2f(SCORE_CELL_WIDTH, SCORE_CELL_HEIGHT),
                                POS[cnt],
                                textureCell);
            cell[cnt]=ScoreCell(score, background);
            ++cnt;
        }

        fin.close();
        if (!quitTexture.loadFromFile("assets/Image/Button/Quit.png")) {
            cout << "Loading quit error\n";
        }

        const Vector2f quitSize = Vector2f(240, 80);

        quitRect.setSize(quitSize);
        quitRect.setPosition(Vector2f((SCREEN_WIDTH - 240) / 2, SCREEN_HEIGHT - 125));
        quitRect.setTexture(quitTexture);
    }

    int run(Player *player) {
        sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return false;
			}
            if (event.type == sf::Event::MouseButtonPressed) {
                auto pos = sf::Mouse::getPosition(*this->window);
                if (quitRect.is_Clicked(sf::Vector2f(pos.x, pos.y)) == 1) {
                    return 0;
                }
            }
		}

		this->window->clear(sf::Color::Black);
        this->window->draw(this->loadSprite);
        for(int i=0; i<7; ++i)
            cell[i].draw(window, "Level " + to_string(i+1));
        this->window->draw(this->quitRect.getRect());
		this->window->display();

		return 8;
    }
};

#endif