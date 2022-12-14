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
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


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

    Player character(Vector2u(10, 2), 10);

    //View view(Vector2f(0, 0), Vector2f(1080, 720));

    const int numRoad = 10;

    const int ROADSIZE = 120;
    const int DISTANCE = 20;
    const int STARTPOS = 120;

    Texture startPavementTexture;
    startPavementTexture.loadFromFile(ROADPATH + "0.png");
    Rectangle startPavementRect(Vector2f(SCREEN_WIDTH, 120), Vector2f(0, 0), startPavementTexture);

    vector <Road> lstRoad;

    for (int i = 0; i < numRoad; i++) {
        int state = Rand(1, 4);
        Rectangle tmpRect(Vector2f(SCREEN_WIDTH, ROADSIZE), Vector2f(0, STARTPOS + (ROADSIZE + DISTANCE) * i), roadTexture[state]);
        Road tmpRoad(tmpRect);

        lstRoad.push_back(tmpRoad);
    }


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        window.clear(Color::White);

        window.draw(startPavementRect.getRect());

        for (auto i : lstRoad) {
            window.draw(i.getRect());
        }

        character.updatePos(event, 0.1);
        character.updateSprite(1);
        character.draw(window);
        //view.setCenter(characterRect.getPosition());
        //window.setView(view);

        window.display();
    }
}