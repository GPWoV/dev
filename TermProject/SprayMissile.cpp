#include "SprayMissile.h"

SprayMissile::SprayMissile(int x, int y) :speed(20), damage(5) {
	this->x = x;
	this->y = y;
	this->state = true;
}

SprayMissile::~SprayMissile() { }

int SprayMissile::getX() {
	return this->x;
}

int SprayMissile::getY() {
	return this->y;
}

bool SprayMissile::getState() {
	return this->state;
}

void SprayMissile::move(int direction, int turret_x, int turret_y) {
	this->x += speed;
	int temp_x = this->x - turret_x;
	switch (direction) {
	case 0:
		this->y = turret_y + int(temp_x * 0.5);
		break;
	case 1:
		this->y = turret_y;
		break;
	case 2:
		this->y = turret_y + int(temp_x * -0.5);
	}
}

bool SprayMissile::crash(int x, int y, int w, int h) {
	if (this->x >= x &&
		this->x <= x + w &&
		this->y >= y &&
		this->y <= y + h) {
		this->state = false;
		return true;
	}
	else {
		return false;
	}
}

void SprayMissile::checkOut() {
	if (this->x > (1280 + 25))
		this->state = false;
}