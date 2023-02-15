#pragma once
#ifndef CFF_M_
#define CFF_M_

#include <Windows.h>
#include <String>
#include <SDL.h>
#include <SDL_image.h>


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


const std::string WINDOW_TITLE = "An Implementation of Code.org Painter";


namespace SDL_CF {
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
	void logSDLError(std::ostream& os,
		const std::string& msg, bool fatal = false);
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
	void waitUntilKeyPressed();
	SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* rederer_);
}

#endif
