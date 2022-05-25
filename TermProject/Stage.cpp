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


	//about turret
	turret_kind = NONE; //터렛 종류
	btn_down = false;
	btn_up = false;
	tp = new TylenolPreview(0, 0); //클릭시 보여질 투명한 타이레놀
	hsp = new HandSanitPreview(0, 0); //클릭시 보여질 투명한 손소독제
}

Stage::~Stage()
{
	SDL_DestroyTexture(texture_);
	//SDL_DestroyTexture(start_texture_);

	for (auto iter = tt.begin(); iter != tt.end(); iter++) { //생성한 터렛들을 지워줌
		delete (*iter);
	}
	tt.clear();

	for (auto iter = hs.begin(); iter != hs.end(); iter++) { //생성한 터렛들을 지워줌
		delete (*iter);
	}
	hs.clear();
}

void Stage::Update()
{
	for (int i = 0; i < tylenol_delay.size(); i++) { //타이레놀 딜레이 걸어서 슈팅
		if (tylenol_delay[i] > tt[i]->delay) {
			tt[i]->shooting();
			tylenol_delay[i] = 0;
		}
		else {
			tylenol_delay[i]++;
		}
	}

	for (int i = 0; i < hand_sanit_delay.size(); i++) { //손소독제 딜레이 걸어서 슈팅
		if (hand_sanit_delay[i] > hs[i]->delay) {
			hs[i]->shooting();
			hand_sanit_delay[i] = 0;
		}
		else {
			hand_sanit_delay[i]++;
		}
	}

	for (auto iter = tt.begin(); iter != tt.end(); iter++) { //타이레놀 미사일 이동 및 삭제
		(*iter)->missileMove();
		(*iter)->missileCheck();
	}

	for (auto iter = hs.begin(); iter != hs.end(); iter++) { //타이레놀 미사일 이동 및 삭제
		(*iter)->missileMove();
		(*iter)->missileCheck();
	}

	tp->setXY(move_x, move_y); //투명한 타이레놀 위치 지정
	hsp->setXY(move_x, move_y);
}


void Stage::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	//SDL_RenderCopy(g_renderer, start_texture_, &start_source_rectangle_, &start_destination_rectangle_);

	for (auto iter = tt.begin(); iter != tt.end(); iter++) { //터렛, 미사일 띄우기
		(*iter)->show();
		(*iter)->missileShow();
	}

	for (auto iter = hs.begin(); iter != hs.end(); iter++) { //터렛, 미사일 띄우기
		(*iter)->show();
		(*iter)->missileShow();
	}

	if (btn_down) {//버튼이 눌렸을 때만 투명한 타이레놀을 보여주겠다.
		switch (turret_kind) {
		case TYLENOL:
			tp->show();
			break;
		case HANDSANIT:
			hsp->show();
			break;
		default:
			break;
		}
		
	}

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

				btn_up = false;
				if (event.button.x > 97 &&
					event.button.x<177 &&
					event.button.y>595 &&
					event.button.y < 695) {
					turret_kind = TYLENOL;
				}
				else if (event.button.x > 202 &&
					event.button.x < 282 &&
					event.button.y>595 &&
					event.button.y < 695) {
					turret_kind = HANDSANIT;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				btn_up = true;
			}
			break;

		default:
			break;
		}
	}

	SDL_PumpEvents();
	buttons = SDL_GetMouseState(&move_x, &move_y);
	if ((buttons & SDL_BUTTON_LMASK) != 0) {
		if (turret_kind != NONE) {
			btn_down = true;
		}
	}
	else {
		if (btn_up && btn_down) {
			if (move_x < 50)
				move_x = 50;
			if (move_x > 1230)
				move_x = 1230;
			if (move_y < 50)
				move_y = 50;
			if (move_y > 520)
				move_y = 520;

			switch (turret_kind) {
			case TYLENOL:
				tt.push_back(new Tylenol({ move_x, move_y }));
				tylenol_delay.push_back(33);
				break;
			case HANDSANIT:
				hs.push_back(new HandSanitizers({ move_x, move_y }));
				hand_sanit_delay.push_back(99);
				break;
			default:
				break;
			}
			btn_up = false;
			btn_down = false;
			turret_kind = NONE;
		}
	}
}
