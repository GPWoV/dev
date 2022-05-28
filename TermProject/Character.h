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

	SDL_Texture* hp_texture;
	SDL_Rect hp_source;
	SDL_Rect hp_destination;


	TTF_Font* font;
	SDL_Texture* gold_num_texture;
	SDL_Rect gold_num_destination;

public:
	int character_hp;
	const int w;
	const int h;

	int gold_int = 5000;
	const char* gold_char;
	char buf[10];
	int goverment_gold = 200;

	bool damage_state = false;
	bool game_state = true;

	Character();
	~Character();
	void show();
	void getDamage(int missile_damage);
	void addGold(int gold);
	void useGold(int turret_price);
	void Renewal();
};