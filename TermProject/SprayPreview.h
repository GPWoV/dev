#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;

class SprayPreview {
private:
	SDL_Texture* spray_texture;
	SDL_Rect spray_source;
	SDL_Rect spray_destination;

public:
	int x, y;
	SprayPreview(int x, int y);
	~SprayPreview();
	void setXY(int x, int y);
	void show();
	void reset();
};

