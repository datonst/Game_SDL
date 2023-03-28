#pragma once
#ifndef MENU_
#define MENU_
#include "Text.h"
#include "CommonFunction.h"
#include <time.h>
#include <vector>
#include "ThreatObject.h"
#include "Audio.h"
namespace Menu {
	bool game_over(SDL_Renderer* renderer, Audio& audio_game);
	int showMenu(SDL_Renderer* renderer, SDL_Texture* g_menu, Audio& audio_game);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
	int showMenuStart(SDL_Renderer* renderer, SDL_Texture* g_menu,Audio& audio_game);
}
#endif