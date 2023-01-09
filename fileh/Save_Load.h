#pragma once
#include <iostream>
#include <fstream>
using namespace std;

void save_game(string playerName, int skinID, int level, int heart);

void load_game(string playerName, int& skinID, int& level, int& heart);