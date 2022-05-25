#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;

class SupportPreview {
private:
	SDL_Texture* support_texture;
	SDL_Rect support_source;
	SDL_Rect support_destination;

public:
	int x, y;
	SupportPreview(int x, int y);
	~SupportPreview();
	void setXY(int x, int y);
	void show();
	void reset();
};

