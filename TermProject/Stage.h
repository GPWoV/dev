#pragma once
#include "SDL.h"
#include "Tylenol.h"
#include "TylenolPreview.h"
#include "HandSanitizers.h"

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

	//about turret
	int turret_kind;
	vector<int>tylenol_delay;
	vector<int>hand_sanit_delay;
	vector<Tylenol*> tt;
	TylenolPreview* tp;
	vector<HandSanitizers*> hs;

	bool btn_down;
	bool btn_up;
	int move_x;
	int move_y;

	Uint32 buttons;
};
