#define _CRT_SECURE_NO_WARNINGS
#define ONE_SECOND 1000 // 1초 초기화
#include "Character.h"
#include <atlstr.h>
#include <string.h>

Character::Character() : character_hp(1000), w(250), h(250) {
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
	gameover_destination = { (1280 - gameover_source.w / 2) / 2, (720 - gameover_source.h / 2) / 2, gameover_source.w / 2, gameover_source.h / 2 };


	//골드
	font = TTF_OpenFont("../../Resources/game_over.ttf", 150);
	SDL_Color black = { 0, 0, 0, 0 };

	sprintf_s(buf, "%d", gold_int);
	gold_char = buf;
	SDL_Surface* gold_num_surface = TTF_RenderText_Blended(font, gold_char, black);
	gold_num_destination = { 0, 0, gold_num_surface->w, gold_num_surface->h };
	gold_num_texture = SDL_CreateTextureFromSurface(g_renderer, gold_num_surface);
	SDL_FreeSurface(gold_num_surface);

}

Character::~Character() {
	SDL_DestroyTexture(character_texture);
	SDL_DestroyTexture(damage_texture);
	SDL_DestroyTexture(gold_num_texture);
	SDL_DestroyTexture(gameover_texture);
	SDL_DestroyTexture(hp_texture);

}

void Character::show() {
	SDL_Rect character_r;
	SDL_Rect damage_r;
	SDL_Rect gold_num_r;
	SDL_Rect hp_r;
	SDL_Rect gameover_r;


	//gold_num
	SDL_Color black = { 0, 0, 0, 0 };
	sprintf_s(buf, "%d", gold_int);
	gold_char = buf;
	SDL_Surface* gold_num_surface = TTF_RenderText_Blended(font, gold_char, black);
	gold_num_destination = { 0, 0, gold_num_surface->w, gold_num_surface->h };
	gold_num_texture = SDL_CreateTextureFromSurface(g_renderer, gold_num_surface);
	SDL_FreeSurface(gold_num_surface);


	gold_num_r = { 950, 600, gold_num_destination.w, gold_num_destination.h };
	SDL_RenderCopy(g_renderer, gold_num_texture, &gold_num_destination, &gold_num_r);


	//hp
	SDL_RenderCopy(g_renderer, hp_texture, &hp_source, &hp_destination);


	//캐릭터, 데미지
	if (damage_state == false) {
		character_r = { character_destination.x, character_destination.y, character_destination.w, character_destination.h };
		SDL_RenderCopy(g_renderer, character_texture, &character_source, &character_destination);
	}
	else {
		damage_r = { character_destination.x, character_destination.y, damage_destination.w, damage_destination.h };
		SDL_RenderCopy(g_renderer, damage_texture, &damage_source, &damage_destination);
		damage_state = false;
	}

	if (game_state == false) {
		gameover_r = { (1280 - gameover_destination.w / 2) / 2, (720 - gameover_destination.h / 2) / 2, gameover_destination.w / 2, gameover_destination.h / 2 };
		SDL_RenderCopy(g_renderer, gameover_texture, &gameover_source, &gameover_destination);
	}
}

void Character::getDamage(int missile_damage) {
	damage_state = true;
	this->hp_destination.w -= missile_damage;
	if (hp_destination.w <= 0) {
		game_state = false;
	}
}


void Character::addGold() {
	if (game_state == true) {
		gold_int += goverment_gold; //1골드씩
	}
}

void Character::useGold(int turret_price) {
	gold_int -= turret_price;
}