#include "HandSanitMissile.h"

HandSanitMissile::HandSanitMissile(int x, int y) : speed(10), damage(5) { //�� ģ���� �������� ������ �� �ӵ�
	this->x = x;
	this->y = y;
	this->state = true;
}

HandSanitMissile::~HandSanitMissile() { }

int HandSanitMissile::getX() {
	return this->x;
}

int HandSanitMissile::getY() {
	return this->y;
}

bool HandSanitMissile::getState() {
	return this->state;
}

void HandSanitMissile::move() {
	this->x += speed;
}

bool HandSanitMissile::crash(int x, int y, int w, int h) {
	if (this->x >= x &&
		this->x <= x + w &&
		this->y+30 >= y &&
		this->y+30 <= y + h) {
		this->state = false;
		return true;
	}
	else {
		return false;
	}
}

void HandSanitMissile::checkOut() {
	if (this->x > (1280 + 25))
		this->state = false;
}