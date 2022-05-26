#pragma once
#include "common.h"
#include "HandSanitMissile.h"
#include <list>

extern SDL_Renderer* g_renderer;

class HandSanitizers {
private:
	SDL_Texture* hand_sanit_texture;
	SDL_Rect hand_sanit_source;
	SDL_Rect hand_sanit_destination;

	SDL_Texture* missile_texture;
	SDL_Rect missile_source;
	SDL_Rect missile_destination;

public:
	const int gold;
	const int w;
	const int h;
	const int delay;

	list<HandSanitMissile> missile;

	HandSanitizers(int x, int y);
	~HandSanitizers();
	int getX();
	int getY();
	void show();
	void shooting();
	void missileMove();
	void missileShow();
	void missileCheck();
};