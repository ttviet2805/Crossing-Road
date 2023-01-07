#pragma once
#include<string>

class Mediator {
private:

public:
	Mediator() {}
	virtual ~Mediator() {}

	virtual void returnLastPos() = 0;
	virtual void updateLastPavement(int pos) = 0;

	virtual void updateLevelText(std::string src) = 0;
	virtual void updateHeartText(std::string src) = 0;
	virtual void updateSpeedText(std::string src) = 0;
	virtual void updateScoreText(std::string src) = 0;
};