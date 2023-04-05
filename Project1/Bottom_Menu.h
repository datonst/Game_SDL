#pragma once
#ifndef BOTTOM_MENU_
#define BOTTOM_MENU_
#include "Text.h"
#include "CommonFunction.h"
#include <time.h>
#include <vector>
#include "ThreatObject.h"
#include "MainObject.h"

namespace Bottom {
	
	void bottom_start_menu(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, MainO& human, gameMap& tx, Text& time_game, std::vector<threatObject*>& list_bear);
	void initBear(std::vector<threatObject*>& list_bear, SDL_Renderer* g_renderer);
}

namespace Crash {
	bool is_crash(const SDL_Rect& object1, const SDL_Rect& object2);
	bool Crash_Object(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, MainO& human,Map& ga_map, Explosion& exp, std::vector<threatObject*>& list_bear, Audio& audio_game);
}
#endif // BOTTOM_MENU_

