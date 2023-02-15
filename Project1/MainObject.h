#pragma once
#ifndef Main_O
#define Main_O

#include "BaseObject.h"
#include "tile_map.h"
const int WIDTH_FRAME = 480;
const int HEIGHT_FRAME = 64;

#define RUN_X 6
#define RUN_Y 8
struct bottom {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};
class MainO : public baseObject {
private:
	bool clip_chay;
	int plus_x;
	int plus_y;
	SDL_Rect clip_mainO;
	SDL_Rect clip[8];
	int index;
	bottom check;
public:
	MainO();
	~MainO();
	void move_mainO  (SDL_Event event, SDL_Renderer* renderer_mainO);
	void Renderer_mainO(const Map& map_data, SDL_Renderer* renderer_mainO);
	void set_clip();
	void UpdateImage(SDL_Renderer* renderer_mainO);
	void check_map(const Map&  map_data);
};
#endif