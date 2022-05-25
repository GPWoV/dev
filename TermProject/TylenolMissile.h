#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;

class TylenolMissile {
private:
	int x, y;
	bool state;
public:
	const int speed;
	const int damage;
	TylenolMissile(int x, int y);
	~TylenolMissile();
	int getX();
	int getY();
	bool getState();
	void move();
	bool crash(int x, int y, int w, int h);
	void checkOut();
};