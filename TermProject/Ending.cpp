#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Ending.h"
#include "Phase.h"
#include "Tylenol.h"
#include "HandSanitizers.h"
#include "Spray.h"
#include "Vaccine.h"
#include "Support.h"
#include "Character.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
extern int renewal;

extern Character* character;

extern vector<int>tylenol_delay;
extern vector<int>hand_sanit_delay;
extern vector<int>spray_delay;
extern vector<int>vaccine_delay;
extern vector<int>support_delay;

extern vector<Tylenol*> tylenol_turret;
extern vector<HandSanitizers*> hand_sanit_turret;
extern vector<Spray*>spray_turret;
extern vector<Vaccine*>vaccine_turret;
extern vector<Support*>support_turret;


//intro_music_
extern Mix_Music* intro_music_;

Ending::Ending()
{
	// 인트로 이미지
	SDL_Surface* temp_surface = IMG_Load("../../Resources/background_outro_clear.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w = 1280;
	destination_rectangle_.h = source_rectangle_.h = 720;

	// 재시작 버튼
	SDL_Surface* start_surface = IMG_Load("../../Resources/btn_restart.png");
	restart_texture_ = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);

	SDL_QueryTexture(restart_texture_, NULL, NULL, &restart_source_rectangle_.w, &restart_source_rectangle_.h);

	restart_destination_rectangle_.x = 450;
	restart_destination_rectangle_.y = 553;

	restart_source_rectangle_.x = 0;
	restart_source_rectangle_.y = 0;
	restart_destination_rectangle_.w = restart_source_rectangle_.w = 380;
	restart_destination_rectangle_.h = restart_source_rectangle_.h = 128;

	// 엔딩 BGM
	Mix_VolumeMusic(70);

	ending_music_ = Mix_LoadMUS("../../Resources/ending.mp3");
	if (!ending_music_)
	{
		printf("Couldn't load the Intro music  %s\n", Mix_GetError());
	}

	Mix_FadeInMusic(ending_music_, -1, 2000);

}

Ending::~Ending()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(restart_texture_);
}

void Ending::Update()
{
	tylenol_delay.clear();
	hand_sanit_delay.clear();
	spray_delay.clear();
	vaccine_delay.clear();
	support_delay.clear();
	
	for (auto iter = tylenol_turret.begin(); iter != tylenol_turret.end(); iter++) {
		delete (*iter);
	}
	tylenol_turret.clear();

	for (auto iter = hand_sanit_turret.begin(); iter != hand_sanit_turret.end(); iter++) {
		delete (*iter);
	}
	hand_sanit_turret.clear();

	for (auto iter = spray_turret.begin(); iter != spray_turret.end(); iter++) {
		delete (*iter);
	}
	spray_turret.clear();

	for (auto iter = vaccine_turret.begin(); iter != vaccine_turret.end(); iter++) {
		delete (*iter);
	}
	vaccine_turret.clear();

	for (auto iter = support_turret.begin(); iter != support_turret.end(); iter++) {
		delete (*iter);
	}
	support_turret.clear();
	
	character->Renewal();
}


void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	SDL_RenderCopy(g_renderer, restart_texture_, &restart_source_rectangle_, &restart_destination_rectangle_);

	SDL_RenderPresent(g_renderer);
}



void Ending::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{

				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x > restart_destination_rectangle_.x &&
					mouse_y > restart_destination_rectangle_.y &&
					mouse_x < restart_destination_rectangle_.x + restart_destination_rectangle_.w &&
					mouse_y < restart_destination_rectangle_.y + restart_destination_rectangle_.h
					) {
					Mix_HaltMusic();

					g_current_game_phase = PHASE_INTRO;
					Mix_PlayMusic(intro_music_, -1);
				}
			}
			break;

		default:
			break;
		}
	}
}
