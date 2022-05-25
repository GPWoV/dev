#include "VaccinePreview.h"

VaccinePreview::VaccinePreview(int x, int y) {
	SDL_Surface* vaccine_surface = IMG_Load("../../Resources/turret_04_ vaccine_move.png");
	vaccine_texture = SDL_CreateTextureFromSurface(g_renderer, vaccine_surface);
	SDL_FreeSurface(vaccine_surface);
	vaccine_source = { 0,0,100,100 };
	vaccine_destination = { x, y, vaccine_source.w, vaccine_source.h };
}

VaccinePreview::~VaccinePreview() {
	SDL_DestroyTexture(vaccine_texture);
}

void VaccinePreview::show() {
	SDL_RenderCopy(g_renderer, vaccine_texture, &vaccine_source, &vaccine_destination);
}

void VaccinePreview::setXY(int x, int y) {
	vaccine_destination.x = x - 50;
	vaccine_destination.y = y - 50;
}

void VaccinePreview::reset() {
	vaccine_destination.x = this->x;
	vaccine_destination.y = this->y;
}