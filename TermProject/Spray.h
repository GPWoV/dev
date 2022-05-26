#pragma once
#include "common.h"
#include "SprayMissile.h"
#include <list>

extern SDL_Renderer* g_renderer;

class Spray {
private:
	SDL_Texture* spray_texture;
	SDL_Rect spray_source;
	SDL_Rect spray_destination;

	SDL_Texture* missile_texture;
	SDL_Rect missile_source;
	SDL_Rect top_destination;
	SDL_Rect middle_destination;
	SDL_Rect bottom_destination;

public:
	const int gold;
	const int w;
	const int h;
	const int delay;

	list<SprayMissile*> missile_top;
	list<SprayMissile*> missile_middle;
	list<SprayMissile*> missile_bottom;

	Spray(int x, int y);
	~Spray();
	int getX();
	int getY();
	void show();
	void shooting();
	void missileMove();
	void missileShow();
	void missileCheck();
};

