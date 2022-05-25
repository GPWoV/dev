#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Ending.h"
#include "Phase.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
extern int renewal;

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

}

Ending::~Ending()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(restart_texture_);
}

void Ending::Update()
{

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
					g_current_game_phase = PHASE_INTRO;
				}
			}
			break;

		default:
			break;
		}
	}
}
