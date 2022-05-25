#include "Virus.h"

Virus::Virus(int x, int y, int virus_speed, int virus_gold, int virus_hp, int level, int virus_attack) :  w(100), h(100) {
	SDL_Surface* Virus_surface = IMG_Load("../../Resources/spritesheet.jpg");
	virus_texture = SDL_CreateTextureFromSurface(g_renderer, Virus_surface);
	SDL_FreeSurface(Virus_surface);
	virus_source = virus_img_sources[level];
	virus_destination = { x, y, virus_source.w, virus_source.h };
}

Virus::~Virus() {
	SDL_DestroyTexture(virus_texture);
}

int Virus::getX() {
	return this->virus_destination.x;
}

int Virus::getY() {
	return this->virus_destination.y;
}

//미사일을 맞았을때
void Virus::takeDamage(int missile_damage) {
	this->virus_hp -= missile_damage;
	if (virus_hp <= 0) {
		this->die();
	}
}

//주인공이랑 부딪힐때
int Virus::hitDamage() {

	this->die();
	return virus_attack;
}

//주인공이랑 부딪히거나 체력0
void Virus::die() {

	//게임 골드지급 구현
	
}


void Virus::move() {
	this->virus_destination.x -= virus_speed;

	if (this->virus_destination.x <= 0) {
		this->hitDamage();
	}
}


void Virus::show() {
	SDL_RenderCopy(g_renderer, virus_texture, &virus_source, &virus_destination);
}

