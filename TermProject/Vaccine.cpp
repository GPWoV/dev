#include "Vaccine.h"

Vaccine::Vaccine(int x, int y) : gold(300), w(100), h(100), delay(165) {
	SDL_Surface* vaccine_surface = IMG_Load("../../Resources/turret_04_vaccine.png");
	vaccine_texture = SDL_CreateTextureFromSurface(g_renderer, vaccine_surface);
	SDL_FreeSurface(vaccine_surface);
	vaccine_source = { 0,0,100,100 };
	vaccine_destination = { x - 50, y - 50, vaccine_source.w, vaccine_source.h };

	SDL_Surface* missile_surface = IMG_Load("../../Resources/turret_04_skill.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);
	missile_source = { 0,0,25,25 };
	missile_destination = { 0,0,25,25 };
}

Vaccine::~Vaccine() {
	SDL_DestroyTexture(vaccine_texture);
	SDL_DestroyTexture(missile_texture);
}

int Vaccine::getX() {
	return this->vaccine_destination.x;
}

int Vaccine::getY() {
	return this->vaccine_destination.y;
}

void Vaccine::show() {
	SDL_RenderCopy(g_renderer, vaccine_texture, &vaccine_source, &vaccine_destination);
}

void Vaccine::shooting() {
	VaccineMissile m(this->vaccine_destination.x + 75, this->vaccine_destination.y + 35);
	missile.push_back(m);
}

void Vaccine::missileMove() {
	for (auto iter = missile.begin(); iter != missile.end(); iter++) {
		(*iter).move();
	}
}

void Vaccine::missileShow() {
	for (auto iter = missile.begin(); iter != missile.end(); iter++) {
		int x = (*iter).getX();
		int y = (*iter).getY();
		bool state = (*iter).getState();
		if (state) {
			missile_destination = { x,y,25,25 };
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
		}
	}
}

void Vaccine::missileCheck() {
	for (auto iter = missile.begin(); iter != missile.end(); iter++) {
		(*iter).checkOut();
		if ((*iter).getState() == false) {
			missile.erase(iter);
		}
	}
}