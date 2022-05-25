#define _CRT_SECURE_NO_WARNINGS
#include "Character.h"
#include <atlstr.h>
#include <string.h>

Character::Character(): w(250), h(250) {
	//main 캐릭터
	SDL_Surface* character_surface = IMG_Load("../../Resources/캐릭터");
	character_texture = SDL_CreateTextureFromSurface(g_renderer, character_surface);
	SDL_FreeSurface(character_surface);
	
	SDL_QueryTexture(character_texture, NULL, NULL, &character_source.w, &character_source.h);
	character_destination.x = character_source.x = 0;
	character_destination.y = character_source.y = 0;
	character_destination.w = character_source.w;
	character_destination.h = character_source.h;

	//데미지
	SDL_Surface* damage_surface = IMG_Load("../../Resources/데미지");
	damage_texture = SDL_CreateTextureFromSurface(g_renderer, damage_surface);
	SDL_FreeSurface(damage_surface);

	SDL_QueryTexture(damage_texture, NULL, NULL, &damage_source.w, &damage_source.h);
	damage_destination.x = damage_source.x = 0;
	damage_destination.y = damage_source.y = 0;
	damage_destination.w = damage_source.w;
	damage_destination.h = damage_source.h;


	//게임오버
	SDL_Surface* gameover_surface = IMG_Load("../../Resources/게임오버");
	gameover_texture = SDL_CreateTextureFromSurface(g_renderer, gameover_surface);
	SDL_FreeSurface(gameover_surface);

	SDL_QueryTexture(gameover_texture, NULL, NULL, &gameover_source.w, &gameover_source.h);
	gameover_destination.x = gameover_source.x = 0;
	gameover_destination.y = gameover_source.y = 0;
	gameover_destination.w = gameover_source.w;
	gameover_destination.h = gameover_source.h;


	//골드
	font = TTF_OpenFont("../../Resources/골드.ttf", 70);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* gold_surface = TTF_RenderText_Blended(font, CW2A(L"골드 : ", CP_UTF8), black);

	gold_destination.x = 0;
	gold_destination.y = 0;
	gold_destination.w = gold_surface->w;
	gold_destination.h = gold_surface->h;

	gold_texture = SDL_CreateTextureFromSurface(g_renderer, gold_surface);
	SDL_FreeSurface(gold_surface);

	gold_char = "0";
	sprintf(buf, "%05d", gold_int);
	gold_char = buf;
	SDL_Surface* gold_num_surface = TTF_RenderText_Blended(font, gold_char, black);

	gold_num_destination.x = 0;
	gold_num_destination.y = 0;
	gold_num_destination.w = gold_num_surface->w;
	gold_num_destination.h = gold_num_surface->h;

	gold_num_texture = SDL_CreateTextureFromSurface(g_renderer, gold_num_surface);
	SDL_FreeSurface(gold_num_surface);

}

Character::~Character() {
	SDL_DestroyTexture(character_texture);
}

void Character::show() {

	SDL_Rect gold_r;
	gold_r.x = 100;
	gold_r.y = 600;
	gold_r.w = gold_destination.w;
	gold_r.h = gold_destination.h;
	SDL_RenderCopy(g_renderer, gold_texture, &gold_destination, &gold_r);

	//gold_num
	SDL_Rect gold_num_r;
	gold_num_r.x = 200;
	gold_num_r.y = 600;
	gold_num_r.w = gold_num_destination.w;
	gold_num_r.h = gold_num_destination.h;
	SDL_RenderCopy(g_renderer, gold_num_texture, &gold_destination, &gold_num_r);

	if (damage_state == false) {
		SDL_RenderCopy(g_renderer, character_texture, &character_source, &character_destination);
	}
	else {
		SDL_RenderCopy(g_renderer, damage_texture, &damage_source, &damage_destination);
		SDL_Delay(100);
		damage_state = false;
	}

	if (game_state == false) {
		SDL_RenderCopy(g_renderer, gameover_texture, &gameover_source, &gameover_destination);
	}
}

void Character::getDamage(int missile_damage) {
	damage_state = true;
	this->character_hp -= missile_damage;
	if (character_hp <= 0) {
		game_state = false;
	}
}

void Character::addGold() {
	//보조금 ttf
}


void Character::useGold(int turret_price) {
	//보조금 ttf
}