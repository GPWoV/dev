#pragma once
#include "common.h"

class SprayMissile {
private:
	int x, y;
	bool state;
public:
	const int speed;
	const int damage;
	SprayMissile(int x, int y);
	~SprayMissile();
	int getX();
	int getY();
	bool getState();
	void move(int direction, int turret_x, int turret_y);
	bool crash(int x, int y, int w, int h);
	void checkOut();
};