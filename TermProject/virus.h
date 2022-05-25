#pragma once
#include "common.h"

extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern phase game_phase;


SDL_Rect virus_img_sources[5] = { {0,0,80,80},{0,0,100,80},{0,0,100,100},{0,0,150,150},{0,0,230,230}};


//바이라스
class Virus {
private:
	SDL_Texture* virus_texture;
	SDL_Rect virus_source;
	SDL_Rect virus_destination;

public:
	int virus_attack;
	int virus_speed;
	int virus_gold;
	int virus_hp;
	int level;
	const int w;
	const int h;
	Virus(int x, int y, int virus_speed, int virus_gold, int virus_hp, int level, int virus_attack);
	~Virus();
	int getX();
	int getY();
	void takeDamage(int missile_damage);
	int hitDamage();
	void die();
	void move();
	void show();
};
