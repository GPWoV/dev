#pragma once
#include "common.h"
#include "TylenolMissile.h"
#include <list>

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern phase game_phase;

class Tylenol {
private:
	SDL_Texture* tylenol_texture;
	SDL_Rect tylenol_source;
	SDL_Rect tylenol_destination;

	SDL_Texture* missile_texture;
	SDL_Rect missile_source;
	SDL_Rect missile_destination;

public:
	const int gold;
	const int w;
	const int h;
	const int delay;

	list<TylenolMissile> missile;

	Tylenol(int x, int y);
	~Tylenol();
	int getX();
	int getY();
	void show();
	void shooting();
	void missileMove();
	void missileShow();
	void missileCheck();
};

