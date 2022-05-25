#include "Tylenol.h"

Tylenol::Tylenol(int x, int y) : gold(300), w(100), h(100) {
	SDL_Surface* tylenol_surface = IMG_Load("../../Resources/tylenolTurret.png");
	//SDL_SetColorKey(tylenol_surface, SDL_TRUE, SDL_MapRGB(tylenol_surface->format, 255, 255, 255));
	tylenol_texture = SDL_CreateTextureFromSurface(g_renderer, tylenol_surface);
	SDL_FreeSurface(tylenol_surface);
	tylenol_source = { 0,0,100,100 };
	tylenol_destination = { x, y, tylenol_source.w, tylenol_source.h };
}

Tylenol::~Tylenol() {
	SDL_DestroyTexture(tylenol_texture);
}

int Tylenol::getX() {
	return this->tylenol_destination.x;
}

int Tylenol::getY() {
	return this->tylenol_destination.y;
}

void Tylenol::show() {
	SDL_RenderCopy(g_renderer, tylenol_texture, &tylenol_source, &tylenol_destination);
}

void Tylenol::shooting() {
	TylenolMissile m(this->tylenol_destination.x, this->tylenol_destination.y);
	missile.push_back(m);
}

void Tylenol::missileMove() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		(*iter).move();
	}
}

void Tylenol::missileShow() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		(*iter).show();
	}
}