#pragma once
#include "SDL.h"
#include "virus.h"
#include "Tylenol.h"
#include "TylenolPreview.h"
#include "HandSanitizers.h"
#include "HandSanitPreivew.h"

#include<cstdlib>
#include<ctime>
using namespace std;

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
	int round;
	
	//about turret
	int turret_kind;
	enum turret{TYLENOL, HANDSANIT, NONE};
	vector<int>tylenol_delay;
	vector<int>hand_sanit_delay;
	vector<Tylenol*> tt;
	TylenolPreview* tp;
	vector<HandSanitizers*> hs;
	HandSanitPreview* hsp;

	bool btn_down;
	bool btn_up;
	int move_x;
	int move_y;

	Uint32 buttons;
};
