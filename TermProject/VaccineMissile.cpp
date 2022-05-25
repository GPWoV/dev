#include "VaccineMissile.h"

VaccineMissile::VaccineMissile(int x, int y) :speed(35), damage(1000) {
	this->x = x;
	this->y = y;
	this->state = true;
}

VaccineMissile::~VaccineMissile() { }

int VaccineMissile::getX() {
	return this->x;
}

int VaccineMissile::getY() {
	return this->y;
}

bool VaccineMissile::getState() {
	return this->state;
}

void VaccineMissile::move() {
	this->x += speed;
}

bool VaccineMissile::crash(int x, int y, int w, int h) {
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

void VaccineMissile::checkOut() {
	if (this->x > (1280 + 25))
		this->state = false;
}