#include "SupportPreview.h"

SupportPreview::SupportPreview(int x, int y) {
	SDL_Surface* support_surface = IMG_Load("../../Resources/turret_05_ support_move.png");
	support_texture = SDL_CreateTextureFromSurface(g_renderer, support_surface);
	SDL_FreeSurface(support_surface);
	support_source = { 0,0,100,100 };
	support_destination = { x, y, support_source.w, support_source.h };
}

SupportPreview::~SupportPreview() {
	SDL_DestroyTexture(support_texture);
}

void SupportPreview::show() {
	SDL_RenderCopy(g_renderer, support_texture, &support_source, &support_destination);
}

void SupportPreview::setXY(int x, int y) {
	support_destination.x = x - 50;
	support_destination.y = y - 50;
}

void SupportPreview::reset() {
	support_destination.x = this->x;
	support_destination.y = this->y;
}