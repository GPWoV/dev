#include "Virus.h"


Virus::Virus(int x, int y, int virus_speed, int virus_gold, int virus_hp, int level, int virus_attack) {
	SDL_Surface* Virus_surface = IMG_Load("../../Resources/virus_spritesheet.png");
	//기타옵션
	this->x = x;
	this->y = y;
	this->virus_speed = virus_speed;
	this->virus_gold = virus_gold;
	this->virus_hp = virus_hp;
	this->virus_attack = virus_attack;

	//바이러스
	this->virus_texture = SDL_CreateTextureFromSurface(g_renderer, Virus_surface);
	this->virus_source = virus_img_sources[level];
	this->virus_destination = { this->x, this->y, virus_source.w, virus_source.h };

	//체력바
	this->virus_hp_texture = SDL_CreateTextureFromSurface(g_renderer, Virus_surface);
	this->virus_hp_source = { 0 ,213,230,17 };
	this->virus_hp_destination = { virus_destination.x, virus_destination.y - 20, (int)(virus_source.w*virus_hp/100), virus_hp_source.h };
	SDL_FreeSurface(Virus_surface);

	

}

Virus::~Virus() {
	SDL_DestroyTexture(virus_texture);
	SDL_DestroyTexture(virus_hp_texture);
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
		//게임 골드지급 구현
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
	//벡터로 해제 해주는 작업필요
}


void Virus::move(){
	this->virus_destination.x -= this->virus_speed;
	this->virus_hp_destination.x -= this->virus_speed;
	this->virus_hp_destination.w -= 2;
	if (this->virus_destination.x <= 227) {
		this->hitDamage();
	}
}


void Virus::show() {
	SDL_RenderCopy(g_renderer, virus_texture, &virus_source, &virus_destination);
	SDL_RenderCopy(g_renderer, virus_hp_texture, &virus_hp_source, &virus_hp_destination);

}

