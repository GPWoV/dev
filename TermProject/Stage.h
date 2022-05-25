#pragma once
#include "SDL.h"
#include "virus.h"

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

	//about virus
	vector<Virus*> flu_list;
	vector<Virus> ebola_list;
	vector<Virus> sars_list;
	vector<Virus> mers_list;
	vector<Virus> corona_list;
	
};
