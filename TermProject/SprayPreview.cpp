#include "SprayPreview.h"

SprayPreview::SprayPreview(int x, int y) {
	SDL_Surface* spray_surface = IMG_Load("../../Resources/turret_01_ tylenol_move.png");
	spray_texture = SDL_CreateTextureFromSurface(g_renderer, spray_surface);
	SDL_FreeSurface(spray_surface);
	spray_source = { 0,0,100,100 };
	spray_destination = { x, y, spray_source.w, spray_source.h };
}

SprayPreview::~SprayPreview() {
	SDL_DestroyTexture(spray_texture);
}

void SprayPreview::show() {
	SDL_RenderCopy(g_renderer, spray_texture, &spray_source, &spray_destination);
}

void SprayPreview::setXY(int x, int y) {
	spray_destination.x = x - 50;
	spray_destination.y = y - 50;
}

void SprayPreview::reset() {
	spray_destination.x = this->x;
	spray_destination.y = this->y;
}