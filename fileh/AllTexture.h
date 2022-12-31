#pragma once

#include <iostream>
#include "Rectangle.h"

class ListTexture {
public:
    const int NUM_ANIMAL_TEXTURE = 12;
	Texture animalTextureLeftRight[5][20];
	Texture animalTextureRightLeft[5][20];

    Texture carTextureLeftRight[8];
    Texture carTextureRightLeft[8];

    Texture trafficLightTexture[5];

    const string OBJECT_PATH = "assets/Image/Object/";

	ListTexture() {
        // Left to Right Dinosaur Texture
		string fileName = "assets/Image/Object/Dinosaur/Left-Right/";

        for (int i = 0; i < NUM_ANIMAL_TEXTURE; i++) {
            if (!animalTextureLeftRight[0][i].loadFromFile(fileName + "Animal" + to_string(i) + ".jpg")) {
                cout << "Loading Animal error\n";
            }
        }

        // Left to Right Dog Texture
        fileName = "assets/Image/Object/Dog/Left-Right/";

        for (int i = 0; i < NUM_ANIMAL_TEXTURE; i++) {
            if (!animalTextureLeftRight[1][i].loadFromFile(fileName + "Animal" + to_string(i) + ".png")) {
                cout << "Loading Animal error\n";
            }
        }

        // Right to Left Dinosaur Texture
        fileName = "assets/Image/Object/Dinosaur/Right-Left/";

        for (int i = 0; i < NUM_ANIMAL_TEXTURE; i++) {
            if (!animalTextureRightLeft[0][i].loadFromFile(fileName + "Animal" + to_string(i) + ".jpg")) {
                cout << "Loading Animal error\n";
            }
        }

        // Right to Left Dog Texture
        fileName = "assets/Image/Object/Dog/Right-Left/";

        for (int i = 0; i < NUM_ANIMAL_TEXTURE; i++) {
            if (!animalTextureRightLeft[1][i].loadFromFile(fileName + "Animal" + to_string(i) + ".png")) {
                cout << "Loading Animal error\n";
            }
        }

        // Car
        carTextureLeftRight[0].loadFromFile(OBJECT_PATH + "Car/Left-Right/Car.png");
        carTextureRightLeft[0].loadFromFile(OBJECT_PATH + "Car/Right-Left/Car.png");
        carTextureLeftRight[1].loadFromFile(OBJECT_PATH + "Truck/Left-Right/Truck.png");
        carTextureRightLeft[1].loadFromFile(OBJECT_PATH + "Truck/Right-Left/Truck.png");
        for (int i = 2; i <= 4; i++) {
            carTextureLeftRight[i].loadFromFile(OBJECT_PATH + "Bus/Bus" + to_string(i - 1) + "/Left-Right/Bus.png");
            carTextureRightLeft[i].loadFromFile(OBJECT_PATH + "Bus/Bus" + to_string(i - 1) + "/Right-Left/Bus.png");
        }

        // Traffic Light
        for (int i = 0; i < 3; i++) {
            if (!trafficLightTexture[i].loadFromFile(OBJECT_PATH + "Traffic-Light/Light" + to_string(i) + ".png")) {
                cout << "Loading image error\n";
            }
        }
	}
};