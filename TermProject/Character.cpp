#include "Character.h"

Character::Character():hp(1000), w(250), h(250) {
	SDL_Surface* character_surface = IMG_Load("../../Resources/캐릭터");
	character_texture = SDL_CreateTextureFromSurface(g_renderer, character_surface);
	SDL_FreeSurface(character_surface);
	character_source = { 0,0,250, 250 }; //캐릭터 크기
	character_destination = { 250, 600, character_source.w, character_source.h };
}

Character::~Character() {
	SDL_DestroyTexture(character_texture);
}

void Character::show() {
	SDL_RenderCopy(g_renderer, character_texture, &character_source, &character_destination);
}
