#pragma once
#ifndef AMM_
#define AMM_

#include "BaseObject.h"
#include "tile_map.h"
#define W_Laser 35
#define H_Laser 5
#define W_Sphere 10
#define H_Sphere 10
class Amop : public baseObject {
private:
	int x_vall, y_vall;
	bool is_move;
	unsigned int amo_type;
	int SPEED_GUN;
	int plus_x;
	int plus_y;
	start start_map;
public:
	enum AmoType {
		NONE,
		Laser,
		sphere
	};
	Amop();
	~Amop();
	void Handle_MM(int const& x_border, int const& y_border);
	unsigned int get_type() const { return amo_type; }
	void  set_is_move(bool move) { is_move = move; }
	bool get_is_move() const { return is_move; }
	void set_W_H(int const& w, int const& h) { rectObject.w = w; rectObject.h = h; }
	void set_X_Y(int const& x, int const& y) { rectObject.x = x; rectObject.y = y; }
	void left_or_right(bool const& x) {
		if (x == true) plus_x = -30;
		else plus_x = 30;
	}
	void change_map_amo(Map& map_data);
	void set_startMap_amo(const int& x, const int& y) { start_map.x = x; start_map.y = y; }
};

#endif
