#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern phase game_phase;

class TylenolMissile {
private:
	SDL_Texture* missile_texture;
	SDL_Rect missile_source;
	SDL_Rect missile_destination;
	bool state;
public:
	const int speed;
	const int damage;
	TylenolMissile(int x, int y);
	~TylenolMissile();
	int getX();
	int getY();
	void show();
	void move();
	bool crash(int x, int y, int w, int h);
	bool checkOut(int x);
};