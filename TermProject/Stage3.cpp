#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Stage3.h"
#include "Phase.h"

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern bool g_flag_running;
extern int g_current_game_phase;
extern int renewal_stage_3;



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

extern int tylenol_price;
extern int hand_sanitizers_price;
extern int spray_price;
extern int vaccine_price;
extern int support_price;

Stage3::Stage3() : total_virus(15)
{
	//stage01 img
	SDL_Surface* temp_surface = IMG_Load("../../Resources/background_stage_03.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_ = { 0,0,1280,720 };

	//about character
	//character = new Character();
	character->damage_state = false;
	character->game_state = true;

	//about virus
	srand((unsigned int)time(NULL));
	stage_clear = false;
	round = 2;
	virus_delay = 0;
	respawn_count = 0;
	dead_virus = 0;

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

	// 인트로 BGM
	Mix_VolumeMusic(50);

	stage3_music_ = Mix_LoadMUS("../../Resources/stage3.mp3");
	if (!stage3_music_)
	{
		printf("Couldn't load the Intro music  %s\n", Mix_GetError());
	}

	Mix_FadeInMusic(stage3_music_, -1, 2000);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 2, 4096);

	click_ = Mix_LoadWAV("../../Resources/click.wav");
	if (click_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	down_ = Mix_LoadWAV("../../Resources/down.wav");
	if (down_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}

	hit_ = Mix_LoadWAV("../../Resources/hit.wav");
	if (hit_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	tylenol_shot_ = Mix_LoadWAV("../../Resources/tylenol_shot.wav");
	if (tylenol_shot_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	coin_ = Mix_LoadWAV("../../Resources/coin.wav");
	if (coin_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	spray_shot_ = Mix_LoadWAV("../../Resources/spray_shot.wav");
	if (spray_shot_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	sanitizer_shot_ = Mix_LoadWAV("../../Resources/sanitizer_shot.wav");
	if (coin_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	vaccine_shot_ = Mix_LoadWAV("../../Resources/vaccine_shot.wav");
	if (coin_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	game_over_ = Mix_LoadWAV("../../Resources/game_over.wav");
	if (game_over_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	next_level_ = Mix_LoadWAV("../../Resources/next_level.wav");
	if (next_level_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}
	character_hit_ = Mix_LoadWAV("../../Resources/character_hit.wav");
	if (character_hit_ == NULL)
	{
		printf("Couldn't load the wav: %s\n", Mix_GetError());
	}


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

Stage3::~Stage3()
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

void Stage3::Update()
{
	virus_delay++;
	if ((virus_delay > 165) && (respawn_count < total_virus)) {
		virus_delay = 0;
		respawn_count++;
		virus_list.push_back(new Virus({ 1200 + rand() % 20 * 60,rand() % 36 * 10 + 120,3,50,200,round,20,true }));
	}

	if (stage_clear) {
		Mix_HaltMusic();
		renewal_stage_3 = 1;

		SDL_Delay(2000);
		g_current_game_phase = PHASE_STAGE_4;
		Mix_PlayMusic(stage4_music_, -1);
	}

	//virus 움직임,자기소멸,캐릭터한테 데미지 주기 구현완료
	for (auto iter = virus_list.begin(); iter != virus_list.end(); iter++) {
		int count = 0;
		for (auto coord_iter = slow_coord.begin(); coord_iter != slow_coord.end(); coord_iter++) {
			if (((*iter)->getX() > (*coord_iter).first - 50) && ((*iter)->getX() < (*coord_iter).first + 300)) {
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

		if (character->game_state) {
			(*iter)->move();
		}
		if (!((*iter)->virus_state)) {
			dead_virus++;
			if ((*iter)->getHpW()>0)
			{
				Mix_VolumeChunk(character_hit_, 100);
				Mix_PlayChannel(6, character_hit_, 0);
				character->getDamage((*iter)->virus_attack);
			}
			else {
				Mix_VolumeChunk(coin_, 80);
				Mix_PlayChannel(3, coin_, 0);
				character->addGold((*iter)->virus_gold);
			}
			virus_list.erase(iter);
			if (dead_virus == total_virus) {
				printf("stage finish");
				Mix_VolumeChunk(next_level_, 100);
				Mix_PlayChannel(7, next_level_, 0);
				stage_clear = true;
				break;
			}
			iter--;
		}
	}

	for (auto coord_iter = slow_coord.begin(); coord_iter != slow_coord.end(); coord_iter++) {
		slow_coord.erase(coord_iter);
	}
	slow_coord.clear();

	for (int i = 0; i < tylenol_delay.size(); i++) { //Ÿ�̷��� ���� �ɾ ����
		if (tylenol_delay[i] > tylenol_turret[i]->delay) {
			if (character->game_state) {
				Mix_VolumeChunk(tylenol_shot_, 10);
				Mix_PlayChannel(-1, tylenol_shot_, 0);
			}
			tylenol_turret[i]->shooting();
			tylenol_delay[i] = 0;
		}
		else {
			tylenol_delay[i]++;
		}
	}

	for (int i = 0; i < hand_sanit_delay.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (hand_sanit_delay[i] > hand_sanit_turret[i]->delay) {
			if (character->game_state) {
				Mix_VolumeChunk(sanitizer_shot_, 10);
				Mix_PlayChannel(1, sanitizer_shot_, 0);
			}
			hand_sanit_turret[i]->shooting();
			hand_sanit_delay[i] = 0;
		}
		else {
			hand_sanit_delay[i]++;
		}
	}

	for (int i = 0; i < spray_delay.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (spray_delay[i] > spray_turret[i]->delay) {
			if (character->game_state) {
				Mix_VolumeChunk(spray_shot_, 30);
				Mix_PlayChannel(6, spray_shot_, 0);
			}
			spray_turret[i]->shooting();
			spray_delay[i] = 0;
		}
		else {
			spray_delay[i]++;
		}
	}

	for (int i = 0; i < vaccine_turret.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (vaccine_delay[i] > vaccine_turret[i]->delay) {
			if (character->game_state) {
				Mix_VolumeChunk(vaccine_shot_, 50);
				Mix_PlayChannel(2, vaccine_shot_, 0);
			}
			vaccine_turret[i]->shooting();
			vaccine_delay[i] = 0;
		}
		else {
			vaccine_delay[i]++;
		}
	}



	for (int i = 0; i < support_turret.size(); i++) { //�ռҵ�� ���� �ɾ ����
		if (support_delay[i] > support_turret[i]->delay) {
			if (character->game_state) {
				Mix_VolumeChunk(coin_, 80);
				Mix_PlayChannel(3, coin_, 0);
			}
			character->addGold(character->goverment_gold); // from yj / change parameter
			support_delay[i] = 0;
			support_turret[i]->coin_state = true;
		}
		else {
			support_delay[i]++;
		}
	}

	for (auto iter = tylenol_turret.begin(); iter != tylenol_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		if (character->game_state) (*iter)->missileMove();
		(*iter)->missileCheck();

		for (auto iter_missile = (*iter)->missile.begin(); iter_missile != (*iter)->missile.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile).crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					Mix_VolumeChunk(hit_, 100);
					Mix_PlayChannel(4, hit_, 0);
					(*iter_flu)->takeDamage((*iter_missile).damage);
				}
			}
		}
	}

	for (auto iter = hand_sanit_turret.begin(); iter != hand_sanit_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		if (character->game_state) (*iter)->missileMove();
		(*iter)->missileCheck();

		for (auto iter_missile = (*iter)->missile.begin(); iter_missile != (*iter)->missile.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile).crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					slow_coord.push_back({ (*iter_missile).getX(), (*iter_missile).getY() });
				}
			}
		}
	}

	for (auto iter = spray_turret.begin(); iter != spray_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		if (character->game_state) (*iter)->missileMove();
		(*iter)->missileCheck();

		for (auto iter_missile = (*iter)->missile_top.begin(); iter_missile != (*iter)->missile_top.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile)->crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					Mix_VolumeChunk(hit_, 70);
					Mix_PlayChannel(4, hit_, 0);
					(*iter_flu)->takeDamage((*iter_missile)->damage);
				}
			}
		}

		for (auto iter_missile = (*iter)->missile_middle.begin(); iter_missile != (*iter)->missile_middle.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile)->crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					Mix_VolumeChunk(hit_, 70);
					Mix_PlayChannel(4, hit_, 0);
					(*iter_flu)->takeDamage((*iter_missile)->damage);
				}
			}
		}

		for (auto iter_missile = (*iter)->missile_bottom.begin(); iter_missile != (*iter)->missile_bottom.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile)->crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					Mix_VolumeChunk(hit_, 70);
					Mix_PlayChannel(4, hit_, 0);
					(*iter_flu)->takeDamage((*iter_missile)->damage);
				}
			}
		}
	}

	for (auto iter = vaccine_turret.begin(); iter != vaccine_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		if (character->game_state) (*iter)->missileMove();
		(*iter)->missileCheck();

		for (auto iter_missile = (*iter)->missile.begin(); iter_missile != (*iter)->missile.end(); iter_missile++) {
			for (auto iter_flu = virus_list.begin(); iter_flu != virus_list.end(); iter_flu++) {
				if ((*iter_missile).crash((*iter_flu)->getX(), (*iter_flu)->getY(), (*iter_flu)->getW(), (*iter_flu)->getH())) {
					Mix_VolumeChunk(hit_, 70);
					Mix_PlayChannel(4, hit_, 0);
					(*iter_flu)->takeDamage((*iter_missile).damage);
				}
			}
		}
	}

	for (auto iter = support_turret.begin(); iter != support_turret.end(); iter++) { //Ÿ�̷��� �̻��� �̵� �� ���
		if ((*iter)->coin_state)
			if (character->game_state) (*iter)->coinMove();
		(*iter)->coinCheck();
	}

	tylenol_preview->setXY(move_x, move_y); //����� Ÿ�̷��� �ġ ���
	hand_sanit_preview->setXY(move_x, move_y);
	spray_preview->setXY(move_x, move_y);
	vaccine_preview->setXY(move_x, move_y);
	support_preview->setXY(move_x, move_y);
}


void Stage3::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	//SDL_RenderCopy(g_renderer, start_texture_, &start_source_rectangle_, &start_destination_rectangle_);

	character->show();

	for (auto iter = virus_list.begin(); iter != virus_list.end(); iter++) {
		(*iter)->show();
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

	if (stage_clear) {
		character->nextLevel(4);
	}

	//게임오버
	if (!character->game_state) {
		character->gameOver();
	}

	SDL_RenderPresent(g_renderer);

}



void Stage3::HandleEvents()
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
				Mix_HaltMusic();
				g_current_game_phase = PHASE_ENDING;

				Mix_PlayMusic(ending_music_, -1);
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
					event.button.x < 177 &&
					event.button.y>595 &&
					event.button.y < 695) {
					Mix_VolumeChunk(click_, 70);
					Mix_PlayChannel(-1, click_, 0);
					turret_kind = TYLENOL;
				}
				else if (event.button.x > 202 &&
					event.button.x < 282 &&
					event.button.y>595 &&
					event.button.y < 695) {
					Mix_VolumeChunk(click_, 70);
					Mix_PlayChannel(-1, click_, 0);
					turret_kind = HANDSANIT;
				}
				else if (event.button.x > 307 &&
					event.button.x < 387 &&
					event.button.y>595 &&
					event.button.y < 695) {
					Mix_VolumeChunk(click_, 70);
					Mix_PlayChannel(-1, click_, 0);
					turret_kind = SPRAY;
				}
				else if (event.button.x > 412 &&
					event.button.x < 492 &&
					event.button.y>595 &&
					event.button.y < 695) {
					Mix_VolumeChunk(click_, 70);
					Mix_PlayChannel(-1, click_, 0);
					turret_kind = VACCINE;
				}
				else if (event.button.x > 788 &&
					event.button.x < 868 &&
					event.button.y>595 &&
					event.button.y < 695) {
					Mix_VolumeChunk(click_, 70);
					Mix_PlayChannel(-1, click_, 0);
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
			if (move_y < 120)
				move_y = 120;
			if (move_y > 520)
				move_y = 520;

			switch (turret_kind) {
			case TYLENOL:
				if (character->gold_int < tylenol_price) break;
				else {
					tylenol_turret.push_back(new Tylenol({ move_x, move_y }));
					tylenol_delay.push_back(33);
					character->useGold(tylenol_price);
				}
				Mix_VolumeChunk(down_, 70);
				Mix_PlayChannel(-1, down_, 0);
				break;
			case HANDSANIT:
				if (character->gold_int < hand_sanitizers_price) break;
				else {
					hand_sanit_turret.push_back(new HandSanitizers({ move_x, move_y }));
					hand_sanit_delay.push_back(99);
					character->useGold(hand_sanitizers_price);
				}
				Mix_VolumeChunk(down_, 70);
				Mix_PlayChannel(-1, down_, 0);
				break;
			case SPRAY:
				if (character->gold_int < spray_price) break;
				else {
					spray_turret.push_back(new Spray({ move_x, move_y }));
					spray_delay.push_back(66);
					character->useGold(spray_price);
				}
				Mix_VolumeChunk(down_, 70);
				Mix_PlayChannel(-1, down_, 0);
				break;
			case VACCINE:
				if (character->gold_int < vaccine_price) break;
				else {
					vaccine_turret.push_back(new Vaccine({ move_x, move_y }));
					vaccine_delay.push_back(165);
					character->useGold(vaccine_price);
				}
				Mix_VolumeChunk(down_, 70);
				Mix_PlayChannel(-1, down_, 0);
				break;
			case SUPPORT:
				if (character->gold_int < support_price) break;
				else {
					support_turret.push_back(new Support({ move_x, move_y }));
					support_delay.push_back(330);
					character->useGold(support_price);
				}
				Mix_VolumeChunk(down_, 70);
				Mix_PlayChannel(-1, down_, 0);

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

void Stage3::Renewal() {
	stage_clear = false;
	for (auto iter = virus_list.begin(); iter != virus_list.end(); iter++) {
		delete (*iter);
	}
	virus_list.clear();
	vector<Virus*>().swap(virus_list);
	virus_delay = 0;
	respawn_count = 0;
	dead_virus = 0;
}
