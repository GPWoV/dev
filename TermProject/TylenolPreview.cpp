#include "TylenolPreview.h"

TylenolPreview::TylenolPreview(int x, int y) {
	SDL_Surface* tylenol_surface = IMG_Load("../../Resources/tylenolMove.png");
	tylenol_texture = SDL_CreateTextureFromSurface(g_renderer, tylenol_surface);
	SDL_FreeSurface(tylenol_surface);
	tylenol_source = { 0,0,100,100 };
	tylenol_destination = { x, y, tylenol_source.w, tylenol_source.h };
}

TylenolPreview::~TylenolPreview() {
	SDL_DestroyTexture(tylenol_texture);
}

void TylenolPreview::show() {
	SDL_RenderCopy(g_renderer, tylenol_texture, &tylenol_source, &tylenol_destination);
}

void TylenolPreview::setXY(int x, int y) {
	tylenol_destination.x = x;
	tylenol_destination.y = y;
}

void TylenolPreview::reset() {
	tylenol_destination.x = this->x;
	tylenol_destination.y = this->y;
}