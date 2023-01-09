#ifndef TEXT_BOX_H
#define TEXT_BOX_H
// Position for display
#define POS_TEXT_X 100
#define POS_TEXT_Y 100
#define POS_RECT_X 100
#define POS_RECT_Y 100
#define RECT_WIDTH 300
#define RECT_HEIGHT 50
// ASCII + string stuff
#define DELETE_KEY 127
#define MAX_LEN 20
#define NEW_LINE_KEY 10
#define CARRIAGE_RETURN 13
#define BACKSPACE_KEY 8
#include <iostream>
#include "fileh/Rectangle.h"

class TextBox {
private:
    Rectangle background;
    std::string playerInput;
    sf::Text playerText;
    sf::Font font;
    sf::Texture texture[2];
    bool isClick;

public:
    TextBox() {
        isClick=false;
        if(!font.loadFromFile("assets/Font/Lato-Bold.ttf")) {
            std::cout << "Can't load font!!!!" << endl;
        }

        if(!texture[0].loadFromFile("assets/Image/Button/textBoxInitial.png")) {
            std::cout << "Can't load texture!!!!" << endl;
        }

        if(!texture[1].loadFromFile("assets/Image/Button/textBoxChoose.png")) {
            std::cout << "Can't load texture!!!!" << endl;
        }

        background=Rectangle(Vector2f(RECT_WIDTH, RECT_HEIGHT),
                            Vector2f(POS_RECT_X, POS_RECT_Y),
                            texture[0]);

        playerText.setFillColor(sf::Color::White);
        playerText.setFont(font);
        playerText.setCharacterSize(25);
        playerText.setStyle(sf::Text::Bold);
        playerText.setPosition(background.getPosition());
    }

    void setName(sf::Event &event) {
        // cout << (int)event.text.unicode << endl;
        if(!isClick) return;
        if(event.text.unicode==DELETE_KEY||
            event.text.unicode==BACKSPACE_KEY) {
            if(playerInput.size()) {
                playerInput.pop_back();
            }
        }
        else if(event.text.unicode==NEW_LINE_KEY) {
            if(playerInput.size()) {
                playerInput.clear();
            }
        }
        else if(event.text.unicode==CARRIAGE_RETURN) {
            isClick=false;
            setTexture();
        }
        else if(event.text.unicode<DELETE_KEY) {
            if(playerInput.size()<MAX_LEN)
                playerInput+=static_cast<char>(event.text.unicode);
        }
        // playerText.setString("");
        playerText.setString(playerInput);
    }

    void setTexture() {
        background.setTexture(texture[isClick]);
    }

    void draw(sf::RenderWindow *window) {
        window->draw(background.getRect());
        window->draw(playerText);
    }

    int is_Clicked(sf::Vector2f pos) {
        int ret=background.is_Clicked(pos);
        if(ret==1) {
            isClick=true;
            setTexture();
        }
        return ret;
    }
};

#endif