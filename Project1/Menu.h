#pragma once
#ifndef MENU_
#define MENU_
#include "Text.h"
#include "CommonFunction.h"
#include <time.h>
#include <vector>
#include "ThreatObject.h"
#include "Audio.h"
#include <fstream>
#include<string>
namespace Menu {
	void save_game(const int& score, const int& money);
	bool game_over(SDL_Renderer* renderer, Audio& audio_game);
	int showMenu(SDL_Renderer* renderer, SDL_Texture* g_menu, Audio& audio_game, const int& score, const int& money);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
	int showMenuStart(SDL_Renderer* renderer, SDL_Texture* g_menu,Audio& audio_game, const int& score, const int& money);
	void clear_file(std::string path);
}
#endif