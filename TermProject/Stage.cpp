#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Stage.h"
#include "Phase.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
extern int renewal;

Stage::Stage()
{
	// 인트로 이미지
	SDL_Surface* temp_surface = IMG_Load("../../Resources/background_stage_01.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w = 1280;
	destination_rectangle_.h = source_rectangle_.h = 720;

	// 시작 버튼
	/*
		SDL_Surface* start_surface = IMG_Load("../../Resources/start.png");
	start_texture_ = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);

	start_destination_rectangle_.x = 350;
	start_destination_rectangle_.y = 300;

	start_source_rectangle_.x = 0;
	start_source_rectangle_.y = 0;
	start_destination_rectangle_.w = start_source_rectangle_.w = 211;
	start_destination_rectangle_.h = start_source_rectangle_.h = 57;
	*/

}

Stage::~Stage()
{
	SDL_DestroyTexture(texture_);
	//SDL_DestroyTexture(start_texture_);
}

void Stage::Update()
{

}


void Stage::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	//SDL_RenderCopy(g_renderer, start_texture_, &start_source_rectangle_, &start_destination_rectangle_);

	SDL_RenderPresent(g_renderer);
}



void Stage::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_SPACE) {
				g_current_game_phase = PHASE_ENDING;
			}

		case SDL_MOUSEBUTTONDOWN:

			// 우클릭 시 페이즈 전환 ( 스테이지 화면으로 )
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				/*
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x > start_destination_rectangle_.x &&
					mouse_y > start_destination_rectangle_.y &&
					mouse_x < start_destination_rectangle_.x + start_destination_rectangle_.w &&
					mouse_y < start_destination_rectangle_.y + start_destination_rectangle_.h
					) {
					g_current_game_phase = PHASE_STAGE;
					renewal = 1;
				}
				*/

			}
			break;

		default:
			break;
		}
	}
}
