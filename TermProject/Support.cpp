#include "Support.h"

Support::Support(int x, int y) : gold(300), w(100), h(100), delay(330) {
	SDL_Surface* support_surface = IMG_Load("../../Resources/turret_05_support.png");
	support_texture = SDL_CreateTextureFromSurface(g_renderer, support_surface);
	SDL_FreeSurface(support_surface);
	support_source = { 0,0,100,100 };
	support_destination = { x - 50, y - 50, support_source.w, support_source.h };
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

int Support::giveMoney() {
	return 300;
}