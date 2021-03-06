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

	SDL_Texture* level2_texture;
	SDL_Texture* level3_texture;
	SDL_Texture* level4_texture;
	SDL_Texture* level5_texture;
	SDL_Rect level_source;
	SDL_Rect level_destination;

	SDL_Texture* hp_texture;
	SDL_Rect hp_source;
	SDL_Rect hp_destination;

	TTF_Font* font;
	SDL_Texture* gold_num_texture;
	SDL_Rect gold_num_destination;

public:
	int character_hp = 1000;
	int gold_int = 1000;
	int goverment_gold = 50;

	int font_size = 150;

	bool damage_state = false;
	bool game_state = true;

	Character(int character_hp);
	~Character();
	void show();
	void getDamage(int missile_damage);
	void addGold(int gold);
	void useGold(int turret_price);
	void Renewal();
	void nextLevel(int stage);
	void gameOver();
};