#include "../fileh/Save_Load.h"
using namespace std;
void save_game(string playerName, int level, int heart) {
	ofstream fout;
	string path = "assets/PlayerInfo/" + playerName + ".txt";
	fout.open(path);
	fout << level << endl;
	fout << heart << endl;
	fout.close();
}

void load_game(string playerName, int& level, int& heart) {
	ifstream fin;
	string path = "assets/PlayerInfo/" + playerName + ".txt";
	fin.open(path);
	fin >> level;
	fin >> heart;
	fin.close();
}