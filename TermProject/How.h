#pragma once
#include "SDL.h"

extern Mix_Music* intro_music_;
extern Mix_Music* stage_music_;

class How
{
public:
	How();
	~How();
	void HandleEvents();
	void Update();
	void Render();

private:
	SDL_Texture* texture_;
	SDL_Rect source_rectangle_;
	SDL_Rect destination_rectangle_;

	SDL_Texture* start_texture_;
	SDL_Rect start_source_rectangle_;
	SDL_Rect start_destination_rectangle_;
};
