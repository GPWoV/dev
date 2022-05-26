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
	//stage01 img
	SDL_Surface* temp_surface = IMG_Load("../../Resources/background_stage_01.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_ = {0,0,1280,720};

	//about character
	character = new Character();
	character->damage_state = false;
	character->game_state = true;

	//about virus
	srand((unsigned int)time(NULL));
	round = 1;
	for (int virus_cnt = 0; virus_cnt < 10; virus_cnt++)
		virus_list.push_back(new Virus({ 1200 + rand() % 20 *60,rand() % 10 * 50 + 20,5,100,100,round,10,true }));
	
	
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

	tylenol_preview = new TylenolPreview(0, 0); //Ŭ���� ������ ����� Ÿ�̷���
	hand_sanit_preview = new HandSanitPreview(0, 0); //Ŭ���� ������ ����� �ռҵ��
	spray_preview = new SprayPreview(0, 0);
	vaccine_preview = new VaccinePreview(0, 0);
	support_preview = new SupportPreview(0, 0);

}

Stage::~Stage()
{
	SDL_DestroyTexture(texture_);
	//SDL_DestroyTexture(start_texture_);
	for (auto iter = virus_list.begin(); iter != virus_list.end(); iter++) { //���� �ͷ���� �����
		delete (*iter);
	}
	virus_list.clear();

	for (auto iter = tylenol_turret.begin(); iter != tylenol_turret.end(); iter++) { //���� �ͷ���� �����
		delete (*iter);
	}
	tylenol_turret.clear();

	for (auto iter = hand_sanit_turret.begin(); iter != hand_sanit_turret.end(); iter++) { //���� �ͷ���� �����
		delete (*iter);
	}
	hand_sanit_turret.clear();

	for (auto iter = spray_turret.begin(); iter != spray_turret.end(); iter++) { //���� �ͷ���� �����
		delete (*iter);
	}
	spray_turret.clear();

	for (auto iter = vaccine_turret.begin(); iter != vaccine_turret.end(); iter++) { //���� �ͷ���� �����
		delete (*iter);
	}
	vaccine_turret.clear();
	vaccine_turret.clear();

	for (auto iter = support_turret.begin(); iter != support_turret.end(); iter++) { //���� �ͷ���� �����
		delete (*iter);
	}
	support_turret.clear();
}

void Stage::Update()
{

	//virus 움직임,자기소멸,캐릭터한테 데미지 주기 구현완료
	for (auto iter = virus_list.begin(); iter != virus_list.end(); iter++) {
		int count = 0;
		for(auto coord_iter = slow_coord.begin(); coord_iter != slow_coord.end(); coord_iter++){
			if (((*iter)->getX() > (*coord_iter).first-50) && ((*iter)->getX() < (*coord_iter).first + 300)) {
				if (((*coord_iter).second + 30 > (*iter)->getY()) && ((*coord_iter).second + 30 < (*iter)->getY() + (*iter)->getH())) {
					(*iter)->slow_state = true;
					(*iter)->slow_delay = 0;
				}
			}
		}

		if ((*iter)->slow_delay < 66) {
			(*iter)->slow_delay++;
			(*iter)->virus_speed = 1;
		}
		else {
			(*iter)->virus_speed = (*iter)->virus_default_speed;
		}

		(*iter)->move();
		if (!((*iter)->virus_state)) {
			character->getDamage(10);
			virus_list.erase(iter);
			iter--;
		}
	}

	for (auto coord_iter = slow_coord.begin(); coord_iter != slow_coord.end(); coord_iter++) {
		slow_coord.erase(coord_iter);
	}
	slow_coord.clear();

    for (int i = 0; i < tylenol_delay.size(); i++) { //Ÿ�̷��� ���� �ɾ ����
		if (tylenol_delay[i] > tylenol_turret[i]->delay) {
			tylenol_turret[i]->shooting();
			tylenol_delay[i] = 0;
		}
		else {
			tylenol_delay[i]++;
		}
	}

	for (int i = 0; i < hand_sanit_delay.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (hand_sanit_delay[i] > hand_sanit_turret[i]->delay) {
			hand_sanit_turret[i]->shooting();
			hand_sanit_delay[i] = 0;
		}
		else {
			hand_sanit_delay[i]++;
		}
	}

	for (int i = 0; i < spray_delay.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (spray_delay[i] > spray_turret[i]->delay) {
			spray_turret[i]->shooting();
			spray_delay[i] = 0;
		}
		else {
			spray_delay[i]++;
		}
	}

	for (int i = 0; i < vaccine_turret.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (vaccine_delay[i] > vaccine_turret[i]->delay) {
			vaccine_turret[i]->shooting();
			vaccine_delay[i] = 0;
		}
		else {
			vaccine_delay[i]++;
		}
	}

	

	for (int i = 0; i < support_turret.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (support_delay[i] > support_turret[i]->delay) {
			character->addGold();
			support_delay[i] = 0;
			support_turret[i]->coin_state = true;
		}
		else {
			support_delay[i]++;
		}
	}

	for (auto iter = tylenol_turret.begin(); iter != tylenol_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		(*iter)->missileMove();
		(*iter)->missileCheck();
		
		for (auto iter_missile = (*iter)->missile.begin(); iter_missile != (*iter)->missile.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile).crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					(*iter_flu)->takeDamage((*iter_missile).damage);
				}
			}
		}
	}

	for (auto iter = hand_sanit_turret.begin(); iter != hand_sanit_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		(*iter)->missileMove();
		(*iter)->missileCheck();

		for (auto iter_missile = (*iter)->missile.begin(); iter_missile != (*iter)->missile.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile).crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					printf("crash.\n");
					slow_coord.push_back({ (*iter_missile).getX(), (*iter_missile).getY() });
				}
			}
		}
	}

	for (auto iter = spray_turret.begin(); iter != spray_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		(*iter)->missileMove();
		(*iter)->missileCheck();

		for (auto iter_missile = (*iter)->missile_top.begin(); iter_missile != (*iter)->missile_top.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile)->crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					(*iter_flu)->takeDamage((*iter_missile)->damage);
				}
			}
		}

		for (auto iter_missile = (*iter)->missile_middle.begin(); iter_missile != (*iter)->missile_middle.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile)->crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					(*iter_flu)->takeDamage((*iter_missile)->damage);
				}
			}
		}

		for (auto iter_missile = (*iter)->missile_bottom.begin(); iter_missile != (*iter)->missile_bottom.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile)->crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					(*iter_flu)->takeDamage((*iter_missile)->damage);
				}
			}
		}
	}

	for (auto iter = vaccine_turret.begin(); iter != vaccine_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		(*iter)->missileMove();
		(*iter)->missileCheck();

		for (auto iter_missile = (*iter)->missile.begin(); iter_missile != (*iter)->missile.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile).crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					(*iter_flu)->takeDamage((*iter_missile).damage);
				}
			}
		}
	}

	for (auto iter = support_turret.begin(); iter != support_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		if((*iter)->coin_state)
			(*iter)->coinMove();
		(*iter)->coinCheck();
	}

	tylenol_preview->setXY(move_x, move_y); //����� Ÿ�̷��� �ġ ���
	hand_sanit_preview->setXY(move_x, move_y);
	spray_preview->setXY(move_x, move_y);
	vaccine_preview->setXY(move_x, move_y);
	support_preview->setXY(move_x, move_y);
}


void Stage::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);
	
	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	//SDL_RenderCopy(g_renderer, start_texture_, &start_source_rectangle_, &start_destination_rectangle_);
	
	character->show();

  for (auto iter = virus_list.begin(); iter != virus_list.end(); iter++) {
		(*iter)-> show();
	}
	
  
	for (auto iter = tylenol_turret.begin(); iter != tylenol_turret.end(); iter++) { //�ͷ�, �̻��� ����
		(*iter)->show();
		(*iter)->missileShow();
	}

	for (auto iter = hand_sanit_turret.begin(); iter != hand_sanit_turret.end(); iter++) { //�ͷ�, �̻��� ����
		(*iter)->show();
		(*iter)->missileShow();
	}

	for (auto iter = spray_turret.begin(); iter != spray_turret.end(); iter++) { //�ͷ�, �̻��� ����
		(*iter)->show();
		(*iter)->missileShow();
	}

	for (auto iter = vaccine_turret.begin(); iter != vaccine_turret.end(); iter++) { //�ͷ�, �̻��� ����
		(*iter)->show();
		(*iter)->missileShow();
	}

	for (auto iter = support_turret.begin(); iter != support_turret.end(); iter++) { //�ͷ�, �̻��� ����
		(*iter)->show();
		if ((*iter)->coin_state)
			(*iter)->coinShow();
	}

	if (btn_down) {//��ư�� ����� ���� ����� Ÿ�̷���� �����ְڴ�.
		switch (turret_kind) {
		case TYLENOL:
			tylenol_preview->show();
			break;
		case HANDSANIT:
			hand_sanit_preview->show();
			break;
		case SPRAY:
			spray_preview->show();
			break;
		case VACCINE:
			vaccine_preview->show();
			break;
		case SUPPORT:
			support_preview->show();
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
				else if (event.button.x > 307 &&
					event.button.x < 387 &&
					event.button.y>595 &&
					event.button.y < 695) {
					turret_kind = SPRAY;
				}
				else if (event.button.x > 412 &&
					event.button.x < 492 &&
					event.button.y>595 &&
					event.button.y < 695) {
					turret_kind = VACCINE;
				}
				else if (event.button.x > 788 &&
					event.button.x < 868 &&
					event.button.y>595 &&
					event.button.y < 695) {
					turret_kind = SUPPORT;
				}
				else {
					turret_kind = NONE;
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
				if (character->gold_int < 300) break;
				else {
					tylenol_turret.push_back(new Tylenol({ move_x, move_y }));
					tylenol_delay.push_back(33);
					character->useGold(300);
				}
				break;
			case HANDSANIT:
				if (character->gold_int < 500) break;
				else {
					hand_sanit_turret.push_back(new HandSanitizers({ move_x, move_y }));
					hand_sanit_delay.push_back(99);
					character->useGold(500);
				}
				break;
			case SPRAY:
				if (character->gold_int < 700) break;
				else {
					spray_turret.push_back(new Spray({ move_x, move_y }));
					spray_delay.push_back(66);
					character->useGold(700);
				}
				break;
			case VACCINE:
				if (character->gold_int < 1000) break;
				else {
					vaccine_turret.push_back(new Vaccine({ move_x, move_y }));
					vaccine_delay.push_back(165);
					character->useGold(1000);
				}
				break;
			case SUPPORT:
				if (character->gold_int < 5000) break;
				else {
					support_turret.push_back(new Support({ move_x, move_y }));
					support_delay.push_back(330);
					character->useGold(5000);
				}
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
