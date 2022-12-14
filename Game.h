#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "fileh/Rectangle.h"
#include "fileh/Road.h"
#include "fileh/Player.h"
using namespace std;
using namespace sf;

const string ROADPATH = "image/Road/Road";

int Rand(int l, int r) {
    return l + (rand()) % (r - l + 1);
}

void gameRun() {
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing Road");

    Texture roadTexture[5];
    for (int i = 0; i < 5; i++) {
        string path = ROADPATH + to_string(i) + ".png";
        roadTexture[i].loadFromFile(path);
    }

    Player player(Vector2u(10, 2), 0.1, Vector2f(64, 120), Vector2f(0, 0), 64, 120, "image/human_walk_sprite.png");

    //Texture characterText;
    //characterText.loadFromFile("image/Amongus.png");
    //Rectangle characterRect(Vector2f(100, 100), Vector2f(0, 0), characterText);

    View view(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    const int numRoad = 21;

    const int ROADSIZE = 120;
    const int DISTANCE = 5;

    vector <Road> lstRoad;

    for (int i = 0; i < numRoad; i++) {
        if (i % 5 == 0) {
            Rectangle tmpRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * i), roadTexture[0]);
            Road tmpRoad(tmpRect);

            lstRoad.push_back(tmpRoad);
            continue;
        }
        int state = Rand(1, 4);
        Rectangle tmpRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, (ROADSIZE + DISTANCE) * i), roadTexture[state]);
        Road tmpRoad(tmpRect);

        lstRoad.push_back(tmpRoad);
    }


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        window.clear(Color::White);

        for (auto i : lstRoad) {
            window.draw(i.getRect());
        }

        //characterRect.characterMove(0.5);
        //window.draw(characterRect.getRect());

        player.updatePos(0.5);
        player.updateSprite(0.5);

        Vector2f characterPos = player.getRect().getPosition();
        characterPos.x = SCREEN_WIDTH / 2;
        characterPos.y = (characterPos.y > SCREEN_HEIGHT / 2) ? characterPos.y : SCREEN_HEIGHT / 2;
        view.setCenter(characterPos);
        window.setView(view);

        player.draw(window);
        window.display();
    }
}