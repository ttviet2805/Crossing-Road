#pragma once

#include <iostream>
#include "Rectangle.h"

class ListTexture {
public:
    const int NUM_ANIMAL_TEXTURE = 12;
	Texture animalTextureLeftRight[5][20];
	Texture animalTextureRightLeft[5][20];

    Texture carTextureLeftRight;
    Texture carTextureRightLeft;

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
            if (!animalTextureLeftRight[1][i].loadFromFile(fileName + "Animal" + to_string(i) + ".jpg")) {
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

        // Right to Left Dinosaur Texture
        fileName = "assets/Image/Object/Dog/Right-Left/";

        for (int i = 0; i < NUM_ANIMAL_TEXTURE; i++) {
            if (!animalTextureRightLeft[1][i].loadFromFile(fileName + "Animal" + to_string(i) + ".jpg")) {
                cout << "Loading Animal error\n";
            }
        }

        // Car
        carTextureLeftRight.loadFromFile(OBJECT_PATH + "Car/Left-Right/Car.png");
        carTextureRightLeft.loadFromFile(OBJECT_PATH + "Car/Right-Left/Car.png");

        // Traffic Light
        for (int i = 0; i < 3; i++) {
            if (!trafficLightTexture[i].loadFromFile(OBJECT_PATH + "Traffic-Light/Light" + to_string(i) + ".png")) {
                cout << "Loading image error\n";
            }
        }
	}
};