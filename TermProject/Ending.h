#pragma once
#include "SDL.h"

extern Mix_Music* ending_music_;

class Ending
{
public:
	Ending();
	~Ending();
	void HandleEvents();
	void Update();
	void Render();

private:
	SDL_Texture* texture_;
	SDL_Rect source_rectangle_;
	SDL_Rect destination_rectangle_;

	SDL_Texture* restart_texture_;
	SDL_Rect restart_source_rectangle_;
	SDL_Rect restart_destination_rectangle_;
};
