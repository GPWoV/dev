#define _CRT_SECURE_NO_WARNINGS
#define ONE_SECOND 1000 // 1√  √ ±‚»≠
#include "Character.h"
#include <atlstr.h>
#include <string.h>

Character::Character() : character_hp(1000), w(250), h(250) {
	//main ƒ≥∏Ø≈Õ
	SDL_Surface* character_surface = IMG_Load("../../Resources/character_normal.png");
	character_texture = SDL_CreateTextureFromSurface(g_renderer, character_surface);
	SDL_FreeSurface(character_surface);

	SDL_QueryTexture(character_texture, NULL, NULL, &character_source.w, &character_source.h);
	character_destination.x = 40;
	character_destination.y = 220;
	character_destination.w = character_source.w;
	character_destination.h = character_source.h;

	//µ•πÃ¡ˆ
	SDL_Surface* damage_surface = IMG_Load("../../Resources/character_attacked.png");
	damage_texture = SDL_CreateTextureFromSurface(g_renderer, damage_surface);
	SDL_FreeSurface(damage_surface);

	SDL_QueryTexture(damage_texture, NULL, NULL, &damage_source.w, &damage_source.h);
	damage_destination.x = damage_source.x = 0;
	damage_destination.y = damage_source.y = 0;
	damage_destination.w = damage_source.w;
	damage_destination.h = damage_source.h;

	//√º∑¬πŸ
	SDL_Surface* hp_surface = IMG_Load("../../Resources/virus_spritesheet.png");
	hp_texture = SDL_CreateTextureFromSurface(g_renderer, hp_surface);
	SDL_FreeSurface(hp_surface);
	hp_source = { 0 ,213,230,17 };
	hp_destination = { character_destination.x, character_destination.y - 20, (int)(character_source.w * character_hp / 1000), hp_source.h };

	//∞‘¿”ø¿πˆ
	SDL_Surface* gameover_surface = IMG_Load("../../Resources/text_gameover.png");
	gameover_texture = SDL_CreateTextureFromSurface(g_renderer, gameover_surface);
	SDL_FreeSurface(gameover_surface);

	SDL_QueryTexture(gameover_texture, NULL, NULL, &gameover_source.w, &gameover_source.h);
	gameover_destination.x = gameover_source.x = 0;
	gameover_destination.y = gameover_source.y = 0;
	gameover_destination.w = gameover_source.w;
	gameover_destination.h = gameover_source.h;


	//∞ÒµÂ
	font = TTF_OpenFont("../../Resources/game_over.ttf", 70);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* gold_surface = TTF_RenderText_Blended(font, CW2A(L"∞ÒµÂ : ", CP_UTF8), black);

	gold_destination.x = 0;
	gold_destination.y = 0;
	gold_destination.w = gold_surface->w;
	gold_destination.h = gold_surface->h;

	gold_texture = SDL_CreateTextureFromSurface(g_renderer, gold_surface);
	SDL_FreeSurface(gold_surface);

	sprintf_s(buf, "%d", gold_int);
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
	SDL_DestroyTexture(damage_texture);
	SDL_DestroyTexture(gold_texture);
	SDL_DestroyTexture(gold_num_texture);
	SDL_DestroyTexture(gameover_texture);
	SDL_DestroyTexture(hp_texture);

}

void Character::show() {
	SDL_Rect character_r;
	SDL_Rect damage_r;
	SDL_Rect gold_r;
	SDL_Rect gold_num_r;
	SDL_Rect hp_r;
	SDL_Rect gameover_r;

	//gold ±€ææ
	gold_r.x = 910;
	gold_r.y = 600;
	gold_r.w = gold_destination.w;
	gold_r.h = gold_destination.h;
	SDL_RenderCopy(g_renderer, gold_texture, &gold_destination, &gold_r);

	//gold_num
	gold_num_r.x = 1010;
	gold_num_r.y = 600;
	gold_num_r.w = gold_num_destination.w;
	gold_num_r.h = gold_num_destination.h;
	SDL_RenderCopy(g_renderer, gold_num_texture, &gold_destination, &gold_num_r);

	//hp
	SDL_RenderCopy(g_renderer, hp_texture, &hp_source, &hp_destination);



	if (damage_state == false) {
		character_r.x = 40;
		character_r.y = 220;
		character_r.w = character_destination.w;
		character_r.h = character_destination.h;
		SDL_RenderCopy(g_renderer, character_texture, &character_source, &character_destination);
	}
	else {
		damage_r.x = 40;
		damage_r.y = 220;
		damage_r.w = damage_destination.w;
		damage_r.h = damage_destination.h;
		SDL_RenderCopy(g_renderer, damage_texture, &damage_source, &damage_destination);
		SDL_Delay(100);
		damage_state = false;
	}

	if (game_state == false) {
		gameover_r.x = 1280 - gameover_destination.w / 2;
		gameover_r.y = 720 - gameover_destination.h / 2;
		gameover_r.w = gameover_destination.w;
		gameover_r.h = gameover_destination.h;
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
	while (game_state == true) {
		gold_int += goverment_gold; //100∞ÒµÂ
		Sleep(ONE_SECOND); //1√  ∞£∞›¿∏∑Œ ∞ÒµÂ »πµÊ
	}
}


void Character::useGold(int turret_price) {
	gold_int -= turret_price;
}