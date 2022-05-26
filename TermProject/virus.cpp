#include "Virus.h"

Mix_Chunk* dead_;

Virus::Virus(int x, int y, int virus_speed, int virus_gold, int virus_hp, int level, int virus_attack, bool virus_state) {
	SDL_Surface* Virus_surface = IMG_Load("../../Resources/virus_sprite.png");
	//��Ÿ�ɼ�
	this->x = x;
	this->y = y;
	this->virus_speed = virus_speed;
	this->virus_gold = virus_gold;
	this->virus_hp = virus_hp;
	this->virus_attack = virus_attack;
	this->virus_state= virus_state;

	//���̷���
	this->virus_texture = SDL_CreateTextureFromSurface(g_renderer, Virus_surface);
	this->virus_source = virus_img_sources[level];
	this->virus_destination = { this->x, this->y, virus_source.w, virus_source.h };

	//ü�¹�
	this->virus_hp_texture = SDL_CreateTextureFromSurface(g_renderer, Virus_surface);
	this->virus_hp_source = { 0 ,213,230,17 };
	this->virus_hp_destination = { virus_destination.x, virus_destination.y - 20, (int)(virus_source.w*virus_hp/100), virus_hp_source.h };
	SDL_FreeSurface(Virus_surface);

	//����
	dead_ = Mix_LoadWAV("../../Resources/dead.wav");
	if (dead_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}

}

Virus::~Virus() {
	SDL_DestroyTexture(virus_texture);
	SDL_DestroyTexture(virus_hp_texture);
	if (dead_) Mix_FreeChunk(dead_);
}

int Virus::getX() {
	return this->virus_destination.x;
}

int Virus::getY() {
	return this->virus_destination.y;
}

int Virus::getW() {
	return this->virus_destination.w;
}

int Virus::getH() {
	return this->virus_destination.h;
}

//�̻����� �¾�����
void Virus::takeDamage(int missile_damage) {
	this->virus_hp_destination.w -= missile_damage;
	if (this->virus_hp_destination.w <= 0) {
		//���� ������� ����
		this->die();
	}
}

//���ΰ��̶� �ε�����
int Virus::hitDamage() {
	this->die();
	return this->virus_attack;
}

//���ΰ��̶� �ε����ų� ü��0
void Virus::die() {
	Mix_VolumeChunk(dead_, 100);
	Mix_PlayChannel(5, dead_, 0);
	this->virus_state = false;
}


void Virus::move(){
	this->virus_destination.x -= this->virus_speed;
	this->virus_hp_destination.x -= this->virus_speed;
	
	if (this->virus_destination.x <= 227) {
		this->hitDamage();
		this->die();
	}
}


void Virus::show() {
	SDL_RenderCopy(g_renderer, virus_texture, &virus_source, &virus_destination);
	SDL_RenderCopy(g_renderer, virus_hp_texture, &virus_hp_source, &virus_hp_destination);

}

