#include "TylenolMissile.h"

TylenolMissile::TylenolMissile(int x, int y) :speed(25), damage(20) {
	this->x = x;
	this->y = y;
	this->state = true;
}

TylenolMissile::~TylenolMissile() { }

int TylenolMissile::getX() {
	return this->x;
}

int TylenolMissile::getY() {
	return this->y;
}

bool TylenolMissile::getState() {
	return this->state;
}

void TylenolMissile::move() {
	this->x += speed;
}

bool TylenolMissile::crash(int x, int y, int w, int h) {
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

void TylenolMissile::checkOut() {
	if (this->x > (1280 + 25))
		this->state = false;
}