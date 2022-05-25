#include "SDL.h"
#include <iostream>
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Phase.h"
#include "Intro.h"
#include "How.h"
#include "Stage.h"
#include "Ending.h"

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
Mix_Music* Music_;

bool g_flag_running;
Uint32 g_last_time_ms;
int g_frame_time_ms = 120;

bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen);
void CleanWindow();


// Game Phases
int g_current_game_phase;
int renewal;

int main(int argc, char* argv[])
{
	InitializeWindow("WoV", 10, 50, 1280, 720, false);

	TTF_Init();

	int audio_rate = 44100;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channels = 2;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0)
	{
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		Mix_CloseAudio();
	}
	else
	{
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		printf("Opened audio at %d Hz %d bit %s\n", audio_rate,
			(audio_format & 0xFF),
			(audio_channels > 2) ? "surround" :
			(audio_channels > 1) ? "stereo" : "mono");

	}

	Stage stage;
	Ending ending;
	Intro intro;
	How how;

	g_last_time_ms = SDL_GetTicks();
	g_current_game_phase = PHASE_INTRO;

	while (g_flag_running)
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < g_frame_time_ms)
			continue;

		if (g_current_game_phase == PHASE_INTRO)
		{

			intro.HandleEvents();
			intro.Update();
			intro.Render();
		}
		else if (g_current_game_phase == PHASE_HOWTOPLAY)
		{
			how.HandleEvents();
			how.Update();
			how.Render();
		}
		else if (g_current_game_phase == PHASE_STAGE)
		{
			stage.HandleEvents();
			stage.Update();
			stage.Render();
		}
		else if (g_current_game_phase == PHASE_ENDING)
		{
			ending.HandleEvents();
			ending.Update();
			ending.Render();
		}

		g_last_time_ms = cur_time_ms;
	}

	CleanWindow();

	Mix_CloseAudio();
	TTF_Quit();

	return 0;
}


bool InitializeWindow(const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		g_window = SDL_CreateWindow(title, xpos, ypos,
			width, height, flags);

		if (g_window != 0) // window init success
		{
			std::cout << "window creation success\n";
			g_renderer = SDL_CreateRenderer(g_window, -1, 0);
			if (g_renderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(g_renderer,
					255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	g_flag_running = true; // everything inited successfully, start the main loop

	return true;
}



void CleanWindow()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_renderer);
	SDL_Quit();
}