#pragma once
#include "common.h"
#include <list>

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern phase game_phase;



//바이라스
class Virus {
private:
	SDL_Texture* virus_texture;
	SDL_Rect virus_source;
	SDL_Rect virus_destination;

	SDL_Texture* virus_hp_texture;
	SDL_Rect virus_hp_source;
	SDL_Rect virus_hp_destination;

public:
	
	SDL_Rect virus_img_sources[5] = { {0,0,80,80},{80,0,80,100},{160,0,100,100},{260,0,150,150},{410,0,230,230} };
	int x,y;
	int virus_attack;
	int virus_speed;
	int virus_default_speed;
	int virus_gold;
	int virus_hp;
	int level;
	bool virus_state;
	bool slow_state;
	int slow_delay;
	Virus(int x, int y, int virus_speed, int virus_gold, int virus_hp, int level, int virus_attack, bool virus_state);
	~Virus();
	int getX();
	int getY();
	int getW();
	int getH();
	int getHpW();
	void takeDamage(int missile_damage);
	int hitDamage();
	void die();
	void move();
	void show();
};
