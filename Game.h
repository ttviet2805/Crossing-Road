#pragma once

const string ROADPATH = "image/Road/Road";

void gameRun() {
    RenderWindow window(VideoMode(1080, 720), "Crossing Road");

    Texture roadTexture[5];
    for (int i = 0; i < 5; i++) {
        string path = ROADPATH + to_string(i) + ".png";
        roadTexture[i].loadFromFile(path);
    }

    Texture characterText;
    characterText.loadFromFile("image/Amongus.png");
    Rectangle characterRect(Vector2f(100, 100), Vector2f(0, 0), characterText);

    View view(Vector2f(0, 0), Vector2f(1080, 720));

    const int numRoad = 10;

    const int distanceX = 200;

    vector <Road> lstRoad;

    for (int i = 0; i < numRoad; i++) {
        Rectangle tmpRect(Vector2f(1080, 100), Vector2f(0, distanceX * i), roadTexture[1]);
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

        characterRect.characterMove(0.5);
        window.draw(characterRect.getRect());
        view.setCenter(characterRect.getPosition());
        window.setView(view);

        window.display();
    }
}