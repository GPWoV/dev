#pragma once
#include "SDL.h"
#include "virus.h"
#include "Tylenol.h"
#include "TylenolPreview.h"
#include "HandSanitizers.h"
#include "HandSanitPreivew.h"
#include "Spray.h"
#include "SprayPreview.h"
#include "Vaccine.h"
#include "VaccinePreview.h"
#include "Support.h"
#include "SupportPreview.h"
#include "Character.h"

#include<cstdlib>
#include<ctime>
using namespace std;

class Stage3
{
public:
	Stage3();
	~Stage3();
	void HandleEvents();
	void Update();
	void Render();
	bool crash();

private:
	SDL_Texture* texture_;
	SDL_Rect source_rectangle_;
	SDL_Rect destination_rectangle_;

	list< pair<int, int> > slow_coord;

	//about virus
	vector<Virus*> virus_list;
	int round;
	bool stage_clear;

	//about turret
	int turret_kind;
	enum turret { TYLENOL, HANDSANIT, SPRAY, VACCINE, SUPPORT, NONE };
	vector<int>tylenol_delay;
	vector<int>hand_sanit_delay;
	vector<int>spray_delay;
	vector<int>vaccine_delay;
	vector<int>support_delay;

	vector<Tylenol*> tylenol_turret;
	vector<HandSanitizers*> hand_sanit_turret;
	vector<Spray*>spray_turret;
	vector<Vaccine*>vaccine_turret;
	vector<Support*>support_turret;

	TylenolPreview* tylenol_preview;
	HandSanitPreview* hand_sanit_preview;
	SprayPreview* spray_preview;
	VaccinePreview* vaccine_preview;
	SupportPreview* support_preview;

	Character* character;



	bool btn_down;
	bool btn_up;
	int move_x;
	int move_y;

	Uint32 buttons;
};
