#pragma once
#include "common.h"
#include "Missile.h"
#include <list>

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern phase game_phase;

class Tylenol {
private:
	SDL_Texture* tylenol_texture;
	SDL_Rect tylenol_source;
	SDL_Rect tylenol_destination;
	list<TylenolMissile> missile;
public:
	const int gold;
	const int w;
	const int h;

	Tylenol(int x, int y);
	~Tylenol();
	int getX();
	int getY();
	void show();
	void shooting();
	void missileMove();
	void missileShow();
};
