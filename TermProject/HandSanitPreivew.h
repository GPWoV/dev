#pragma once
#include "common.h"
extern SDL_Renderer* g_renderer;

class HandSanitPreview {
private:
	SDL_Texture* hand_sanit_texture;
	SDL_Rect hand_sanit_source;
	SDL_Rect hand_sanit_destination;

public:
	int x, y;
	HandSanitPreview(int x, int y);
	~HandSanitPreview();
	void setXY(int x, int y);
	void show();
	void reset();
};