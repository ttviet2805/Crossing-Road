#pragma once

class Mediator {
private:

public:
	Mediator() {}
	virtual ~Mediator() {}

	virtual void returnLastPos(float x, float y) = 0;
};