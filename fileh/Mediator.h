#pragma once

class Mediator {
private:

public:
	Mediator() {}
	virtual ~Mediator() {}

	virtual void returnLastPos() = 0;
	virtual void updateLastPavement(int pos) = 0;
};