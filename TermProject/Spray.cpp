#include "Spray.h"

Spray::Spray(int x, int y) : gold(300), w(100), h(100), delay(66) {
	SDL_Surface* tylenol_surface = IMG_Load("../../Resources/turret_03_spray.png");
	//SDL_SetColorKey(tylenol_surface, SDL_TRUE, SDL_MapRGB(tylenol_surface->format, 255, 255, 255));
	spray_texture = SDL_CreateTextureFromSurface(g_renderer, tylenol_surface);
	SDL_FreeSurface(tylenol_surface);
	spray_source = { 0,0,100,100 };
	spray_destination = { x - 50, y - 50, spray_source.w, spray_source.h };

	SDL_Surface* missile_surface = IMG_Load("../../Resources/turret_03_skill.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);
	missile_source = { 0,0,25,25 };
	missile_destination = { 0,0,25,25 };
}

Spray::~Spray() {
	SDL_DestroyTexture(spray_texture);
	SDL_DestroyTexture(missile_texture);
}

int Spray::getX() {
	return this->spray_destination.x;
}

int Spray::getY() {
	return this->spray_destination.y;
}

void Spray::show() {
	SDL_RenderCopy(g_renderer, spray_texture, &spray_source, &spray_destination);
}

void Spray::shooting() {
	missile_top.push_back(new SprayMissile(this->spray_destination.x + 75, this->spray_destination.y + 35));
	missile_middle.push_back(new SprayMissile(this->spray_destination.x + 75, this->spray_destination.y + 35));
	missile_bottom.push_back(new SprayMissile(this->spray_destination.x + 75, this->spray_destination.y + 35));
}

void Spray::missileMove() {
	for (auto iter = missile_top.begin(); iter != missile_top.end(); iter++) {
		(*iter)->move();
	}
	for (auto iter = missile_middle.begin(); iter != missile_middle.end(); iter++) {
		(*iter)->move();
	}
	for (auto iter = missile_bottom.begin(); iter != missile_bottom.end(); iter++) {
		(*iter)->move();
	}
}

void Spray::missileShow() {
	for (auto iter = missile_top.begin(); iter != missile_top.end(); iter++) {
		int x = (*iter)->getX();
		int y = (*iter)->getY();
		bool state = (*iter)->getState();
		if (state) {
			missile_destination = { x,y,25,25 };
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
		}
	}
	for (auto iter = missile_middle.begin(); iter != missile_middle.end(); iter++) {
		int x = (*iter)->getX();
		int y = (*iter)->getY();
		bool state = (*iter)->getState();
		if (state) {
			missile_destination = { x,y,25,25 };
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
		}
	}
	for (auto iter = missile_bottom.begin(); iter != missile_bottom.end(); iter++) {
		int x = (*iter)->getX();
		int y = (*iter)->getY();
		bool state = (*iter)->getState();
		if (state) {
			missile_destination = { x,y,25,25 };
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
		}
	}
}

void Spray::missileCheck() {
	for (auto iter = missile_top.begin(); iter != missile_top.end(); iter++) {
		(*iter)->checkOut();
		if ((*iter)->getState() == false) {
			missile_top.erase(iter);
			delete* iter;
		}
	}
	for (auto iter = missile_middle.begin(); iter != missile_middle.end(); iter++) {
		(*iter)->checkOut();
		if ((*iter)->getState() == false) {
			missile_top.erase(iter);
			delete* iter;
		}
	}
	for (auto iter = missile_bottom.begin(); iter != missile_bottom.end(); iter++) {
		(*iter)->checkOut();
		if ((*iter)->getState() == false) {
			missile_top.erase(iter);
			delete* iter;
		}
	}
}