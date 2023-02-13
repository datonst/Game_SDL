#include "MainObject.h"

MainO::MainO() { 
	x_mainO_clip = 0;
	y_mainO_clip = 0;
	w_mainO_clip = 60;
	h_mainO_clip = 64;
	clip_chay = false;
};


MainO::~MainO() { ; };


void MainO::move_mainO(SDL_Event event, SDL_Renderer* renderer_mainO) {
	setRectObject(0, 0, 60, 64);
	if (event.type == SDL_KEYDOWN) {
		bool ret;
		switch (event.key.keysym.sym) {
		case SDLK_DOWN: 
			break;
		case SDLK_UP: 
			break;
		case SDLK_LEFT: 
			ret = loadTextureObject("img//player_left.png", renderer_mainO);
			if (ret == true) 
			break;
		case SDLK_RIGHT:
			ret=loadTextureObject("img//player_right.png", renderer_mainO);
			if(ret==true) clip_chay = true;
			break;
		}
	}
	else if (SDL_KEYUP)
	{
		switch (event.key.keysym.sym) {
		case SDLK_DOWN:
			break;
		case SDLK_UP:
			break;
		case SDLK_LEFT:
			x_mainO_clip = 0;
			clip_chay = false;
			break;
		case SDLK_RIGHT:
			x_mainO_clip =0;
			clip_chay = false;
			break;
		}
	}

};


void MainO::Renderer_mainO(SDL_Renderer* renderer_mainO) {
	if (clip_chay == true) {
		if (x_mainO_clip >= WIDTH_FRAME ) x_mainO_clip = 0;
		else x_mainO_clip += WIDTH_FRAME/8;
		rectObject.x+=10;
	}
	SDL_Rect clip_mainO = { clip_mainO.x = x_mainO_clip,clip_mainO.y = y_mainO_clip, clip_mainO.w = w_mainO_clip,clip_mainO.h =h_mainO_clip };
	renderObject(renderer_mainO, &clip_mainO);
};

