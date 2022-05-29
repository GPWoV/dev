#include "HandSanitizers.h"

HandSanitizers::HandSanitizers(int x, int y) : gold(400), w(100), h(100), delay(66) {
	SDL_Surface* hand_sanit_surface = IMG_Load("../../Resources/turret_02_sanitizer.png");
	hand_sanit_texture = SDL_CreateTextureFromSurface(g_renderer, hand_sanit_surface);
	SDL_FreeSurface(hand_sanit_surface);
	hand_sanit_source = { 0,0,100,100 };
	hand_sanit_destination = { x-50, y-50, hand_sanit_source.w, hand_sanit_source.h };

	SDL_Surface* missile_surface = IMG_Load("../../Resources/turret_02_skill.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
	SDL_FreeSurface(missile_surface);
	missile_source = { 0,0,110,60 };
	missile_destination = { 0,0,110,60 };
}

HandSanitizers::~HandSanitizers() {
	SDL_DestroyTexture(hand_sanit_texture);
	SDL_DestroyTexture(missile_texture);
}

int HandSanitizers::getX() {
	return this->hand_sanit_destination.x;
}

int HandSanitizers::getY() {
	return this->hand_sanit_destination.y;
}

void HandSanitizers::show() {
	SDL_RenderCopy(g_renderer, hand_sanit_texture, &hand_sanit_source, &hand_sanit_destination);
}

void HandSanitizers::shooting() {
	HandSanitMissile m(this->hand_sanit_destination.x+50, this->hand_sanit_destination.y-30);
	missile.push_back(m);
}

void HandSanitizers::missileMove() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		(*iter).move();
	}
}

void HandSanitizers::missileShow() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		int x = (*iter).getX();
		int y = (*iter).getY();
		bool state = (*iter).getState();
		if (state) {
			missile_destination = { x,y,110,60 };
			SDL_RenderCopy(g_renderer, missile_texture, &missile_source, &missile_destination);
		}
	}
}

void HandSanitizers::missileCheck() {
	for (auto iter = ++missile.begin(); iter != missile.end(); iter++) {
		(*iter).checkOut();
		if ((*iter).getState() == false) {
			missile.erase(iter);
		}
	}
}