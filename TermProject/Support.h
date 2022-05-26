#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;

class Support {
private:
	SDL_Texture* support_texture;
	SDL_Rect support_source;
	SDL_Rect support_destination;

	SDL_Texture* coin_texture;
	SDL_Rect coin_source;
	SDL_Rect coin_destination;

public:
	const int gold;
	const int w;
	const int h;
	const int delay;
	int coin_x, coin_y;
	bool coin_state;

	Support(int x, int y);
	~Support();
	int getX();
	int getY();
	void show();
	void coinShow();
	void coinMove();
	void coinCheck();
};

