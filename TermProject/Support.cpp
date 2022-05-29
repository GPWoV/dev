#include "Support.h"

Support::Support(int x, int y) : gold(200), w(100), h(100), delay(330) {
	SDL_Surface* support_surface = IMG_Load("../../Resources/turret_05_support.png");
	support_texture = SDL_CreateTextureFromSurface(g_renderer, support_surface);
	SDL_FreeSurface(support_surface);
	support_source = { 0,0,100,100 };
	support_destination = { x - 50, y - 50, support_source.w, support_source.h };

	SDL_Surface* coin_surface = IMG_Load("../../Resources/turret_05_skill.png");
	coin_texture = SDL_CreateTextureFromSurface(g_renderer, coin_surface);
	SDL_FreeSurface(coin_surface);
	coin_source = { 0,0,35,38 };
	coin_destination = { x - 15, y - 68, coin_source.w, coin_source.h };
	coin_state = false;
}

Support::~Support() {
	SDL_DestroyTexture(support_texture);
}

int Support::getX() {
	return this->support_destination.x;
}

int Support::getY() {
	return this->support_destination.y;
}

void Support::show() {
	SDL_RenderCopy(g_renderer, support_texture, &support_source, &support_destination);
}

void Support::coinShow() {
	SDL_RenderCopy(g_renderer, coin_texture, &coin_source, &coin_destination);
}

void Support::coinMove() {
	coin_destination.y -= 10;
}

void Support::coinCheck() {
	if (coin_destination.y < -35) {
		coin_state = false;
		coin_destination.y = support_destination.y - 18;
	}
}