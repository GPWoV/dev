#pragma once
#include "SDL.h"

class Stage
{
public:
	Stage();
	~Stage();
	void HandleEvents();
	void Update();
	void Render();

private:
	SDL_Texture* texture_;
	SDL_Rect source_rectangle_;
	SDL_Rect destination_rectangle_;
};
