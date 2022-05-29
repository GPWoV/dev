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

extern Mix_Music* stage2_music_;
extern Mix_Music* ending_music_;
extern Mix_Music* stage3_music_;

// »ç¿îµå
extern Mix_Chunk* click_;
extern Mix_Chunk* coin_;
extern Mix_Chunk* down_;
extern Mix_Chunk* hit_;
extern Mix_Chunk* tylenol_shot_;
extern Mix_Chunk* spray_shot_;
extern Mix_Chunk* vaccine_shot_;
extern Mix_Chunk* sanitizer_shot_;
extern Mix_Chunk* character_hit_;
extern Mix_Chunk* game_over_;
extern Mix_Chunk* next_level_;

using namespace std;

class Stage2
{
public:
	Stage2();
	~Stage2();
	void HandleEvents();
	void Update();
	void Render();
	void Renewal();
	bool crash();
	void GameOver();

private:
	SDL_Texture* texture_;
	SDL_Rect source_rectangle_;
	SDL_Rect destination_rectangle_;

	list< pair<int, int> > slow_coord;

	//about virus
	vector<Virus*> virus_list;
	int round;
	bool stage_clear;

	const int total_virus;
	int virus_delay;
	int respawn_count;
	int dead_virus;

	//about turret
	int turret_kind;
	enum turret { TYLENOL, HANDSANIT, SPRAY, VACCINE, SUPPORT, NONE };

	TylenolPreview* tylenol_preview;
	HandSanitPreview* hand_sanit_preview;
	SprayPreview* spray_preview;
	VaccinePreview* vaccine_preview;
	SupportPreview* support_preview;

	bool btn_down;
	bool btn_up;
	int move_x;
	int move_y;

	Uint32 buttons;
};
