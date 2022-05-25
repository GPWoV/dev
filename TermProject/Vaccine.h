#pragma once
#include "common.h"
#include "VaccineMissile.h"
#include <list>

extern SDL_Renderer* g_renderer;

class Vaccine {
private:
	SDL_Texture* vaccine_texture;
	SDL_Rect vaccine_source;
	SDL_Rect vaccine_destination;

	list<VaccineMissile> missile;

	SDL_Texture* missile_texture;
	SDL_Rect missile_source;
	SDL_Rect missile_destination;

public:
	const int gold;
	const int w;
	const int h;
	const int delay;

	Vaccine(int x, int y);
	~Vaccine();
	int getX();
	int getY();
	void show();
	void shooting();
	void missileMove();
	void missileShow();
	void missileCheck();
};

