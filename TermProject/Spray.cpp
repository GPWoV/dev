#include "Spray.h"

Spray::Spray(int x, int y) : gold(300), w(100), h(100), delay(33) {
	SDL_Surface* spray_surface = IMG_Load("../../Resources/turret_03_spray.png");
	spray_texture = SDL_CreateTextureFromSurface(g_renderer, spray_surface);
	SDL_FreeSurface(spray_surface);
	spray_source = { 0,0,100,100 };
	spray_destination = { x - 50, y - 50, spray_source.w, spray_source.h };

	SDL_Surface* missile_surface = IMG_Load("../../Resources/turret_03_skill.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);
	missile_source = { 0,0,25,25 };
	top_destination = { 0,0,25,25 };
	middle_destination = { 0,0,25,25 };
	bottom_destination = { 0,0,25,25 };
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
	printf("top missile 생성\n");
	missile_top.push_back(new SprayMissile(this->spray_destination.x + 75, this->spray_destination.y + 35));
	printf("middle missile 생성\n");
	missile_middle.push_back(new SprayMissile(this->spray_destination.x + 75, this->spray_destination.y + 35));
	printf("bottom missile 생성\n");
	missile_bottom.push_back(new SprayMissile(this->spray_destination.x + 75, this->spray_destination.y + 35));
}

void Spray::missileMove() {
	for (auto iter = missile_top.begin(); iter != missile_top.end(); iter++) {
		printf("top missile 이동\n");
		(*iter)->move(0, spray_destination.x, spray_destination.y);
	}
	for (auto iter = missile_middle.begin(); iter != missile_middle.end(); iter++) {
		printf("middle missile 이동\n");
		(*iter)->move(1, spray_destination.x, spray_destination.y);
	}
	for (auto iter = missile_bottom.begin(); iter != missile_bottom.end(); iter++) {
		printf("bottom missile 이동\n");
		(*iter)->move(2, spray_destination.x, spray_destination.y);
	}
}

void Spray::missileShow() {
	for (auto iter = missile_top.begin(); iter != missile_top.end(); iter++) {
		int x = (*iter)->getX();
		int y = (*iter)->getY();
		bool state = (*iter)->getState();
		if (state) {
			top_destination = { x,y,25,25 };
			printf("top 렌더카피\n");
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &top_destination);
		}
	}
	for (auto iter = missile_middle.begin(); iter != missile_middle.end(); iter++) {
		int x = (*iter)->getX();
		int y = (*iter)->getY();
		bool state = (*iter)->getState();
		if (state) {
			middle_destination = { x,y,25,25 };
			printf("middle 렌더카피\n");
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &middle_destination);
		}
	}
	for (auto iter = missile_bottom.begin(); iter != missile_bottom.end(); iter++) {
		int x = (*iter)->getX();
		int y = (*iter)->getY();
		bool state = (*iter)->getState();
		if (state) {
			bottom_destination = { x,y,25,25 };
			printf("bottom 렌더카피\n");
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &bottom_destination);
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
			missile_middle.erase(iter);
			delete* iter;
		}
	}
	for (auto iter = missile_bottom.begin(); iter != missile_bottom.end(); iter++) {
		(*iter)->checkOut();
		if ((*iter)->getState() == false) {
			missile_bottom.erase(iter);
			delete* iter;
		}
	}
}