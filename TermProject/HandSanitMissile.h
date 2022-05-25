#pragma once
#include "common.h"

class HandSanitMissile {
private:
	int x, y;
	bool state;
public:
	const int speed;
	const int damage;
	HandSanitMissile(int x, int y);
	~HandSanitMissile();
	int getX();
	int getY();
	bool getState();
	void move();
	bool crash(int x, int y, int w, int h);
	void checkOut();
};