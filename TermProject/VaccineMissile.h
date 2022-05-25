#pragma once
#include "common.h"

class VaccineMissile {
private:
	int x, y;
	bool state;
public:
	const int speed;
	const int damage;
	VaccineMissile(int x, int y);
	~VaccineMissile();
	int getX();
	int getY();
	bool getState();
	void move();
	bool crash(int x, int y, int w, int h);
	void checkOut();
};