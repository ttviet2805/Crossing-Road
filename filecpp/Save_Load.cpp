#include "../fileh/Save_Load.h"
using namespace std;
void save_game(string playerName, int skinID, int level, int heart) {
	ofstream fout;
	string path = "assets/PlayerInfo/" + playerName + ".txt";
	fout.open(path);
	fout << skinID << endl;
	fout << level << endl;
	fout << heart << endl;
	fout.close();
}

void load_game(string playerName, int& skinID, int& level, int& heart) {
	ifstream fin;
	string path = "assets/PlayerInfo/" + playerName + ".txt";
	fin.open(path);
	fin >> skinID;
	fin >> level;
	fin >> heart;
	fin.close();
}