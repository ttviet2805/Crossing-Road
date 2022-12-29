#include "../fileh/Player.h"

std::string getStr(int num) {
	string ans = "";
	while (num) {
		ans += ((num % 10) + '0');
		num /= 10;
	}
	reverse(ans.begin(), ans.end());
	if (ans.empty()) ans = "0";
	return ans;
}

void Player::changeSpeed(float speed) {
    curSpeed += speed;
}

void Player::updateInfo(std::string newName) {
    name=newName;
}