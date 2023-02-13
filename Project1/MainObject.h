#pragma once
#ifndef Main_O
#define Main_O

#include "BaseObject.h"
const int WIDTH_FRAME=480;
const int HEIGHT_FRAME = 64;

class MainO : public baseObject {
private:
	int x_mainO_clip;
	int y_mainO_clip;
	int w_mainO_clip;
	int h_mainO_clip;
	bool clip_chay;
public:
	MainO();
	~MainO();
	void move_mainO(SDL_Event event, SDL_Renderer* renderer_mainO);
	void Renderer_mainO(SDL_Renderer* renderer_mainO);
};
#endif