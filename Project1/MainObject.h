#pragma once
#ifndef Main_O
#define Main_O

#include "BaseObject.h"
#include "tile_map.h"
#include "Amo.h"
#include <vector>
#include "Menu.h"
#include"Explosion.h"


struct pathPlayer {
	std::string left;
	std::string right;
	std::string jump_left;
	std::string jump_right;
};

struct bottom {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};
class MainO : public baseObject {
private:
	int RUN_X = 10;
	int RUN_Y = 3;
	baseObject winner_object;
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
	int WIDTH_FRAME;
	int HEIGHT_FRAME;
	int number_die;
	int gain_money;
	bool end_round;
	int score;
	std::vector <baseObject*> heart;
	Explosion exp;
	pathPlayer player_images;
	int length_frame;
	int time_speed_left;
	int start_count_speed;
	int restore_heart;
public:
	MainO();
	~MainO();
	void move_mainO(SDL_Event &event, SDL_Renderer* renderer_mainO, Audio& audio_game);
	void set_clip();
	void Renderer_mainO(Map& map_data, SDL_Renderer* renderer_mainO, Audio& audio_game);
	void UpdateImage(SDL_Renderer* renderer_mainO);
	void change_map(Map&  map_data,SDL_Renderer* g_renderer, Audio& audio_game);
	void runMap(const Map& map_data, Audio& audio_game);
	start get_startMap() const { return start_map; }
	void set_startMap(const int& x, const int& y) { if (end_round == false) { start_map.x = x; start_map.y = y; } }
	void delete_amo_object(int const& i) { if (i < p_amo.size()) { p_amo.erase(p_amo.begin() + i); } }
	bool check_run_over(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, Audio& audio_game);
	void set_number_die(int const& x, SDL_Renderer* g_renderer);
	void insertHeart(SDL_Renderer* g_renderer);
	int get_number_die() const { return number_die; }
	bool crash_object_over(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, Audio& audio_game);
	std::vector<Amop*> GetlistAmop() const { return p_amo; }
	void ShowAmo(Map& map_data,SDL_Renderer* renderer_mainO);
	void set_list(std::vector<Amop*> x) { p_amo = x; };
	int get_money() const { return gain_money; }
	void renderer_heart(SDL_Renderer* g_renderer);
	int get_score() const { return score; }
	void add_score(int const&x) { score += x;}
	void change_player(const std::string& l, const std::string& r, const std::string& j_l, const std::string& j_r);
	void resetHuman(SDL_Renderer* g_renderer);
	void dinosaur(SDL_Renderer* g_renderer);
	void wolf(SDL_Renderer* g_renderer);
	bool winner() const { return end_round; }
	void time_speed(Audio& audio_game);
	int get_count_speed() const { return start_count_speed; }
	void resetRunX() { RUN_X = 10; }
	void restore();
	int get_restore_heart() const { return restore_heart; }
	int get_come_back_time() const { return come_back_time; }
};
#endif