#pragma once
#ifndef Threat_O
#define Threat_O

#include "BaseObject.h"
#include "tile_map.h"
#include <vector>
#include<time.h>
#define W_Laserr 35
#define H_Laserr 5
#define WIDTH_THREAT 506
#define HEIGTH_THREAT 64
#define GRAVITY 3
#define SPEED_THREAT 4
#define RANGE_X 60

class threatObject :public baseObject {

private:
	int come_back_time;
	SDL_Rect clip_threat;
	SDL_Rect clip[8];
	int x_val_T;   //locate threat in map
	int y_val_T;
	start start_map;
	int plus_x;
	int plus_y;
	int index;
	bool on_ground;
	bool check_go_left;
	bool check_go_right;
	int right_threat;
	int left_threat;

	baseObject* dan_t_one;
	int plus_dan_threat;
public:
	threatObject();
	~threatObject();
	void set_W_H(int const& w, int const& h) { rectObject.w = w; rectObject.h = h; }
	void set_X_Y(const int& x, const int& y) { x_val_T = x; y_val_T = y; right_threat = x + RANGE_X; left_threat = x - RANGE_X; }
	void set_clip();
	void check_map_threat(Map& map_data);
	void Renderer_threatO(Map& map_data, SDL_Renderer* renderer_threatO);
	void set_startMap(int const& x, int const& y) { start_map.x = x; start_map.y = y; }
	void move_threat(SDL_Renderer* screen);

	baseObject* dan_T_one() const { return dan_t_one; }
	void set_dan_threat(SDL_Renderer* rendererThreat);

};
#endif