#pragma once
#include "common.h"
extern SDL_Renderer* g_renderer;

class TylenolPreview {
private:
	SDL_Texture* tylenol_texture;
	SDL_Rect tylenol_source;
	SDL_Rect tylenol_destination;

public:
	int x, y;
	TylenolPreview(int x, int y);
	~TylenolPreview();
	void setXY(int x, int y);
	void show();
	void reset();
};