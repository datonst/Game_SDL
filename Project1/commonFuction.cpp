﻿#include "CommonFunction.h"
#include <iostream>



bool SDL_CF::initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		SDL_CF::logSDLError(std::cout, "SDL_Init", true);

	window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, 
	// SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == nullptr) SDL_CF::logSDLError(std::cout, "CreateWindow", true);


	//Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);

	//Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
	//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

	if (renderer == nullptr) SDL_CF::logSDLError(std::cout, "CreateRenderer", true);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	//	SDL_SetRenderDrawColor(g_bkground,255,255,255,255);
	//	int imgflag=IMG_INIT_PNG;
	//	if(!IMG_Init(imgflag) && imgflag){
	//		logSDLError(std::cout, "imgflag", true);
	//	}

	//init Audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cerr << "Error Load Open Audio" << Mix_GetError << std::endl;
		return false;
	}
	return true;
}


void SDL_CF::waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}


void SDL_CF::logSDLError(std::ostream& os,
	const std::string& msg, bool fatal)
{
	os << msg << " Error: " << SDL_GetError() << std::endl;
	if (fatal) {
		SDL_Quit();
		exit(1);
	}
}

void SDL_CF::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture* SDL_CF::loadTexture(const std::string& path, SDL_Renderer* renderer, const int& COLOR_KEY_R, const int& COLOR_KEY_G, const int& COLOR_KEY_B) {
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path << "SDL_image Error: " << IMG_GetError();
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) std::cout << "Unable to creat texture from " << path << "SDL Error: " << IMG_GetError();
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}




