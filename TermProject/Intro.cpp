#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Intro.h"
#include "Phase.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
extern int renewal_stage_1;

Intro::Intro()
{

	// 인트로 이미지
	SDL_Surface* temp_surface = IMG_Load("../../Resources/background_intro.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w = 1280;
	destination_rectangle_.h = source_rectangle_.h = 720;

	// 시작 버튼
	SDL_Surface* start_surface = IMG_Load("../../Resources/btn_start.png");
	start_texture_ = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);

	SDL_QueryTexture(start_texture_, NULL, NULL, &start_source_rectangle_.w, &start_source_rectangle_.h);

	start_destination_rectangle_.x = 202;
	start_destination_rectangle_.y = 502;

	start_source_rectangle_.x = 0;
	start_source_rectangle_.y = 0;
	start_destination_rectangle_.w = start_source_rectangle_.w = 380;
	start_destination_rectangle_.h = start_source_rectangle_.h = 128;

	// 게임 방법 버튼
	SDL_Surface* tutorial_surface = IMG_Load("../../Resources/btn_tutorial.png");
	tutorial_texture_ = SDL_CreateTextureFromSurface(g_renderer, tutorial_surface);
	SDL_FreeSurface(tutorial_surface);

	SDL_QueryTexture(tutorial_texture_, NULL, NULL, &tutorial_source_rectangle_.w, &tutorial_source_rectangle_.h);

	tutorial_destination_rectangle_.x = 698;
	tutorial_destination_rectangle_.y = 502;

	tutorial_source_rectangle_.x = 0;
	tutorial_source_rectangle_.y = 0;
	tutorial_destination_rectangle_.w = tutorial_source_rectangle_.w = 380;
	tutorial_destination_rectangle_.h = tutorial_source_rectangle_.h = 128;

	// 인트로 BGM
	Mix_VolumeMusic(50);

	intro_music_ = Mix_LoadMUS("../../Resources/intro.mp3");
	if (!intro_music_)
	{
		printf("Couldn't load the Intro music  %s\n", Mix_GetError());
	}

	Mix_FadeInMusic(intro_music_, -1, 2000);
}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(start_texture_);
	SDL_DestroyTexture(tutorial_texture_);
}

void Intro::Update()
{

}


void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	SDL_RenderCopy(g_renderer, start_texture_, &start_source_rectangle_, &start_destination_rectangle_);
	SDL_RenderCopy(g_renderer, tutorial_texture_, &tutorial_source_rectangle_, &tutorial_destination_rectangle_);

	SDL_RenderPresent(g_renderer);
}



void Intro::HandleEvents()
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

				if (mouse_x > start_destination_rectangle_.x &&
					mouse_y > start_destination_rectangle_.y &&
					mouse_x < start_destination_rectangle_.x + start_destination_rectangle_.w &&
					mouse_y < start_destination_rectangle_.y + start_destination_rectangle_.h
					) {
					Mix_HaltMusic();

					g_current_game_phase = PHASE_STAGE;
					renewal_stage_1 = 1;

					Mix_PlayMusic(stage_music_, -1);
				}

				if (mouse_x > tutorial_destination_rectangle_.x &&
					mouse_y > tutorial_destination_rectangle_.y &&
					mouse_x < tutorial_destination_rectangle_.x + tutorial_destination_rectangle_.w &&
					mouse_y < tutorial_destination_rectangle_.y + tutorial_destination_rectangle_.h
					) {
					g_current_game_phase = PHASE_HOWTOPLAY;
				}

			}
			break;

		default:
			break;
		}
	}
}
