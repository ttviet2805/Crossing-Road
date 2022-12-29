#include "../fileh/Save_Load.h"
using namespace std;
void save_game(int level, int heart) {
	ofstream fout;
	fout.open("save_game.txt");
	fout << level << endl;
	fout << heart << endl;
	fout.close();
}

void load_game(int& level, int& heart) {
	ifstream fin;
	fin.open("assets/save_game.txt");
	fin >> level;
	fin >> heart;
	fin.close();
}