#include "Tylenol.h"

Tylenol::Tylenol(int x, int y) : gold(300), w(100), h(100), delay(33) {
	SDL_Surface* tylenol_surface = IMG_Load("../../Resources/tylenolTurret.png");
	//SDL_SetColorKey(tylenol_surface, SDL_TRUE, SDL_MapRGB(tylenol_surface->format, 255, 255, 255));
	tylenol_texture = SDL_CreateTextureFromSurface(g_renderer, tylenol_surface);
	SDL_FreeSurface(tylenol_surface);
	tylenol_source = { 0,0,100,100 };
	tylenol_destination = { x-50, y-50, tylenol_source.w, tylenol_source.h };

	SDL_Surface* missile_surface = IMG_Load("../../Resources/tylenolMissile.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);
	missile_source = { 0,0,25,25 };
	missile_destination = { 0,0,25,25 };
}

Tylenol::~Tylenol() {
	SDL_DestroyTexture(tylenol_texture);
	SDL_DestroyTexture(missile_texture);
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
	TylenolMissile m(this->tylenol_destination.x+75, this->tylenol_destination.y+35);
	missile.push_back(m);
}

void Tylenol::missileMove() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		(*iter).move();
	}
}

void Tylenol::missileShow() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		int x = (*iter).getX();
		int y = (*iter).getY();
		bool state = (*iter).getState();
		if (state) {
			missile_destination = { x,y,25,25 };
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
		}
	}
}

void Tylenol::missileCheck() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		(*iter).checkOut();
		if ((*iter).getState() == false) {
			missile.erase(iter);
		}
	}
}