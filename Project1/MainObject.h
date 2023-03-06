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
	int number_die;
	int gain_money;
	bool end_round;
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
	void set_startMap(const int& x, const int& y) { if (end_round == false) { start_map.x = x; start_map.y = y; } }
	void delete_amo_object(int const& i) { if (i < p_amo.size()) { p_amo.erase(p_amo.begin() + i); } }
	bool check_run_over(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background);
	void set_number_die(int const& x) { number_die = x; }
	int get_number_die() const { return number_die; }
	bool crash_object(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background);
	std::vector<Amop*> GetlistAmop() const { return p_amo; }
	void ShowAmo(Map& map_data,SDL_Renderer* renderer_mainO);
	void set_list(std::vector<Amop*> x) { p_amo = x; };
	int get_money() const { return gain_money; }
	
};
#endif