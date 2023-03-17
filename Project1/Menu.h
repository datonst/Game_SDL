#pragma once
#ifndef MENU_
#define MENU_
#include "Text.h"
#include "commonFunction.h"
#include <time.h>
#include "ThreatObject.h"

namespace Menu {
	bool game_over(SDL_Renderer* renderer);
	bool showMenu(SDL_Renderer* renderer, SDL_Texture* g_menu);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
	void initBear(std::vector<threatObject*> & list_bear, SDL_Renderer* g_renderer);
}
#endif