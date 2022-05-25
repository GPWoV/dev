#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;
extern bool g_glag_running;
extern phase game_phase;

class Character {
private:
	SDL_Texture* character_texture;
	SDL_Rect character_source;
	SDL_Rect character_destination;

public:
	const int hp;
	const int w;
	const int h;

	Character();
	~Character();
	void show();
};