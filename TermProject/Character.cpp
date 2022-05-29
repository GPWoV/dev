#define _CRT_SECURE_NO_WARNINGS
#include "Character.h"
#include <string.h>

Character::Character(int character_hp) {
	//main 캐릭터
	SDL_Surface* character_surface = IMG_Load("../../Resources/character_normal.png");
	character_texture = SDL_CreateTextureFromSurface(g_renderer, character_surface);
	SDL_FreeSurface(character_surface);

	SDL_QueryTexture(character_texture, NULL, NULL, &character_source.w, &character_source.h);
	character_destination = { 40, 220, character_source.w, character_source.h };

	//데미지
	SDL_Surface* damage_surface = IMG_Load("../../Resources/character_attacked.png");
	damage_texture = SDL_CreateTextureFromSurface(g_renderer, damage_surface);
	SDL_FreeSurface(damage_surface);

	SDL_QueryTexture(damage_texture, NULL, NULL, &damage_source.w, &damage_source.h);
	damage_destination = { character_destination.x, character_destination.y, damage_source.w, damage_source.h };

	//체력바
	SDL_Surface* hp_surface = IMG_Load("../../Resources/virus_sprite.png");
	hp_texture = SDL_CreateTextureFromSurface(g_renderer, hp_surface);
	SDL_FreeSurface(hp_surface);
	hp_source = { 0 ,213,230,17 };
	hp_destination = { character_destination.x, character_destination.y - 20, (int)(character_source.w * character_hp / 1000), hp_source.h };

	//게임오버
	SDL_Surface* gameover_surface = IMG_Load("../../Resources/text_gameover.png");
	gameover_texture = SDL_CreateTextureFromSurface(g_renderer, gameover_surface);
	SDL_FreeSurface(gameover_surface);

	SDL_QueryTexture(gameover_texture, NULL, NULL, &gameover_source.w, &gameover_source.h);
	gameover_destination = { (1280 - gameover_source.w / 2) / 2, (720 - gameover_source.h / 2) / 2, gameover_source.w/2, gameover_source.h/2};

	//넥스트레벨
	SDL_Surface* level2_surface = IMG_Load("../../Resources/STAGE 2 START.png");
	level2_texture = SDL_CreateTextureFromSurface(g_renderer, level2_surface);
	SDL_FreeSurface(level2_surface);

	SDL_QueryTexture(level2_texture, NULL, NULL, &level_source.w, &level_source.h);
	level_destination = { (1280 - level_source.w / 2) / 2, (720 - level_source.h / 2) / 2, level_source.w/2, level_source.h /2};

	SDL_Surface* level3_surface = IMG_Load("../../Resources/STAGE 3 START.png");
	level3_texture = SDL_CreateTextureFromSurface(g_renderer, level3_surface);
	SDL_FreeSurface(level3_surface);

	SDL_QueryTexture(level3_texture, NULL, NULL, &level_source.w, &level_source.h);


	SDL_Surface* level4_surface = IMG_Load("../../Resources/STAGE 4 START.png");
	level4_texture = SDL_CreateTextureFromSurface(g_renderer, level4_surface);
	SDL_FreeSurface(level4_surface);

	SDL_QueryTexture(level4_texture, NULL, NULL, &level_source.w, &level_source.h);


	SDL_Surface* level5_surface = IMG_Load("../../Resources/STAGE 5 START.png");
	level5_texture = SDL_CreateTextureFromSurface(g_renderer, level5_surface);
	SDL_FreeSurface(level5_surface);

	SDL_QueryTexture(level5_texture, NULL, NULL, &level_source.w, &level_source.h);

	//골드
	font = TTF_OpenFont("../../Resources/game_over.ttf", 150);

}

Character::~Character() {
	SDL_DestroyTexture(character_texture);
	SDL_DestroyTexture(damage_texture);
	SDL_DestroyTexture(gold_num_texture);
	SDL_DestroyTexture(gameover_texture);
	SDL_DestroyTexture(hp_texture);
	SDL_DestroyTexture(level2_texture);
	SDL_DestroyTexture(level3_texture);
	SDL_DestroyTexture(level4_texture);
	SDL_DestroyTexture(level5_texture);
}

void Character::show() {
	SDL_Rect gold_num_r;

	//gold_num
	SDL_Color black = { 0, 0, 0, 0 };
	sprintf_s(buf, "%d", gold_int);
	this->gold_char = this->buf;
	SDL_Surface* gold_num_surface = TTF_RenderText_Blended(font, gold_char, black);
	gold_num_destination = { 0, 0, gold_num_surface->w, gold_num_surface->h };
	gold_num_texture = SDL_CreateTextureFromSurface(g_renderer, gold_num_surface);
	SDL_FreeSurface(gold_num_surface);


	gold_num_r = { 950, 600, gold_num_destination.w, gold_num_destination.h };
	SDL_RenderCopy(g_renderer, gold_num_texture, &gold_num_destination, &gold_num_r);


	//hp
	SDL_RenderCopy(g_renderer, hp_texture, &hp_source, &hp_destination);


	//캐릭터, 데미지
	if (this->damage_state == false) {
		SDL_RenderCopy(g_renderer, character_texture, &character_source, &character_destination);
	}
	else {
		SDL_RenderCopy(g_renderer, damage_texture, &damage_source, &damage_destination);
		this->damage_state = false;
	}
}

void Character::getDamage(int missile_damage) {

	this->damage_state = true;
	this->hp_destination.w -= missile_damage;
	if (this->hp_destination.w <= 0) {
		this->game_state = false;
	}
}


void Character::addGold(int gold) {
	if (this->game_state == true) {
		this->gold_int += gold;
	}
}

void Character::useGold(int turret_price) {
	this->gold_int -= turret_price;
}

void Character::Renewal() {
	this->character_hp = 1000;
	this->gold_int = 5000;
	this->damage_state = false;
	this->game_state = true;
	hp_destination = { character_destination.x, character_destination.y - 20, (int)(character_source.w * character_hp / 1000), hp_source.h };
}

void Character::nextLevel(int stage) {

	if (stage == 2) {
		SDL_RenderCopy(g_renderer, level2_texture, &level_source, &level_destination);
	}
	else if (stage == 3) {
		SDL_RenderCopy(g_renderer, level3_texture, &level_source, &level_destination);
	}
	else if (stage == 4) {
		SDL_RenderCopy(g_renderer, level4_texture, &level_source, &level_destination);
	}
	else {
		SDL_RenderCopy(g_renderer, level5_texture, &level_source, &level_destination);
	}
}

void Character::gameOver() {
	SDL_RenderCopy(g_renderer, gameover_texture, &gameover_source, &gameover_destination);
}