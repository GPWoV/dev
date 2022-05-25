#include "HandSanitPreivew.h"

HandSanitPreview::HandSanitPreview(int x, int y) {
	SDL_Surface* hand_sanit_surface = IMG_Load("../../Resources/turret_02_sanitizer_move.png");
	hand_sanit_texture = SDL_CreateTextureFromSurface(g_renderer, hand_sanit_surface);
	SDL_FreeSurface(hand_sanit_surface);
	hand_sanit_source = { 0,0,100,100 };
	hand_sanit_destination = { x, y, hand_sanit_source.w, hand_sanit_source.h };
}

HandSanitPreview::~HandSanitPreview() {
	SDL_DestroyTexture(hand_sanit_texture);
}

void HandSanitPreview::show() {
	SDL_RenderCopy(g_renderer, hand_sanit_texture, &hand_sanit_source, &hand_sanit_destination);
}

void HandSanitPreview::setXY(int x, int y) {
	hand_sanit_destination.x = x - 50;
	hand_sanit_destination.y = y - 50;
}

void HandSanitPreview::reset() {
	hand_sanit_destination.x = this->x;
	hand_sanit_destination.y = this->y;
}