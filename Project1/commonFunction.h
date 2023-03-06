#pragma once
#ifndef CFF_M_
#define CFF_M_

#include <Windows.h>
#include <String>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace SDL_CF{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 640;
	const int SCREEN_BPP = 32;
	const std::string WINDOW_TITLE = "An Implementation of Code.org Painter";
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
	void logSDLError(std::ostream& os,
		const std::string& msg, bool fatal = false);
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
	void waitUntilKeyPressed();
	SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer,const int &COLOR_KEY_R,const int &COLOR_KEY_G, const int &COLOR_KEY_B);
	bool is_crash(const SDL_Rect& object1, const SDL_Rect& object2);
}
#endif
