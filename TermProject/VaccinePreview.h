#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;

class VaccinePreview {
private:
	SDL_Texture* vaccine_texture;
	SDL_Rect vaccine_source;
	SDL_Rect vaccine_destination;

public:
	int x, y;
	VaccinePreview(int x, int y);
	~VaccinePreview();
	void setXY(int x, int y);
	void show();
	void reset();
};

