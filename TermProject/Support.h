#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;

class Support {
private:
	SDL_Texture* support_texture;
	SDL_Rect support_source;
	SDL_Rect support_destination;

public:
	const int gold;
	const int w;
	const int h;
	const int delay;

	Support(int x, int y);
	~Support();
	int getX();
	int getY();
	void show();
};

