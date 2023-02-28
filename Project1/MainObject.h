#pragma once
#ifndef Main_O
#define Main_O

#include "BaseObject.h"
#include "tile_map.h"
#include "Amo.h"
#include <vector>


#define RUN_X 10
#define RUN_Y 3



struct bottom {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};
class MainO : public baseObject {
private:
	bool on_ground;
	bool clip_chay;
	int plus_x;
	int plus_y;
	SDL_Rect clip_mainO;
	SDL_Rect clip[8];
	int index;
	bottom check;
	start start_map;
	bool left_mid;
	int come_back_time;
	std::vector<Amop*> p_amo;
	bool dan_left;
	const int WIDTH_FRAME = 480;
	const int HEIGHT_FRAME = 64;
	const int w_frame = WIDTH_FRAME/8;
	const int h_frame = 64;
public:
	MainO();
	~MainO();
	void move_mainO  (SDL_Event &event, SDL_Renderer* renderer_mainO);
	void Renderer_mainO(Map& map_data, SDL_Renderer* renderer_mainO);
	void set_clip();
	void UpdateImage(SDL_Renderer* renderer_mainO);
	void change_map(Map&  map_data);
	void runMap(const Map& map_data);
	start get_startMap() const { return start_map; }
	void set_startMap(const int&x, const int &y) { start_map.x = x; start_map.y = y; }

	
	std::vector<Amop*> GetlistAmop() const { return p_amo; }
	void ShowAmo(SDL_Renderer* renderer_mainO);
	void set_list(std::vector<Amop*> x) { p_amo = x; };
};
#endif