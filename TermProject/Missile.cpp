#include "Missile.h"

TylenolMissile::TylenolMissile(int x, int y) :speed(30), damage(20) {
	SDL_Surface* missile_surface = IMG_Load("../../Resources/tylenolMissile.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);
	missile_source = { 0,0,25,25 };
	missile_destination = { x, y, missile_source.w, missile_source.h };
	this->state = true;
}

TylenolMissile::~TylenolMissile() {
	SDL_DestroyTexture(missile_texture);
}

int TylenolMissile::getX() {
	return missile_destination.x;
}

int TylenolMissile::getY() {
	return missile_destination.y;
}

void TylenolMissile::show() {
	SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
}

void TylenolMissile::move() {
	missile_destination.x += speed;
}

bool TylenolMissile::crash(int x, int y, int w, int h) {
	if (missile_destination.x >= x &&
		missile_destination.x <= x + w &&
		missile_destination.y >= y &&
		missile_destination.y <= y + h) {
		this->state = false;
	}
	return this->state;
}

bool TylenolMissile::checkOut(int x) {
	if (missile_destination.x > (x + 25)) {
		this->state = false;
	}
	return this->state;
}