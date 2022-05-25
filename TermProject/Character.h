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

	SDL_Texture* damage_texture;
	SDL_Rect damage_source;
	SDL_Rect damage_destination;

	SDL_Texture* gameover_texture;
	SDL_Rect gameover_source;
	SDL_Rect gameover_destination;


	TTF_Font* font;
	SDL_Texture* gold_texture;
	SDL_Rect gold_destination;

public:
	int hp;
	const int w;
	const int h;

	bool damage_state = false;
	bool game_state = true;

	Character();
	~Character();
	void show();
	void getDamage(int missile_damage);
	void addGold();
	void useGold();
};