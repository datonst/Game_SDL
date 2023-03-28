#include "Amo.h"

Amop::Amop() {
	SPEED_GUN = 0;
	x_vall = SPEED_GUN;
	y_vall = SPEED_GUN;
	is_move = false;
	amo_type = 0;
	rectObject.x = 0;
	rectObject.y = 0;
	rectObject.w = 0;
	rectObject.h = 0;
	plus_x = 0;
	plus_y = 0;
	start_map.x = 0;
	start_map.y = 0;
};

Amop::~Amop() {
	;
};


void Amop::Handle_MM(int const& x_border, int const& y_border) {
	rectObject.x += plus_x;
	if (rectObject.x<0 || rectObject.x>x_border) is_move = false;
	if (rectObject.y<0 || rectObject.y>y_border) is_move = false;
};


void Amop::check_map_amo(const Map& map_data) {

	//check horizontal
	int x1 = (rectObject.x + start_map.x + plus_x) / TILE_SIZE;
	int x2 = (rectObject.x + start_map.x + plus_x + W_Laser) / TILE_SIZE;
	int y1 = (rectObject.y + start_map.y) / TILE_SIZE;
	int y2 = (rectObject.y + start_map.y + H_Laser) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (plus_x > 0) {
			if (map_data.tile[y1][x2] == STATE_MONEY || map_data.tile[y2][x2] == STATE_MONEY ||
				map_data.tile[y1][x2] == STATE_AID || map_data.tile[y2][x2] == STATE_AID) { ; }
			else if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0) {
				plus_x = 0;
				is_move = false;
				setRectObject(0, 0, 0, 0);
			}
		}
		else if (plus_x < 0) {
			if (map_data.tile[y1][x1] == STATE_MONEY || map_data.tile[y2][x1] == STATE_MONEY ||
				map_data.tile[y1][x1] == STATE_AID || map_data.tile[y2][x1] == STATE_AID) { ; }
			else if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0) {
				plus_x = 0;
				is_move = false;
				setRectObject(0, 0, 0, 0);
			}
		}
	}

	//check vertical
	x1 = (rectObject.x + start_map.x) / TILE_SIZE;
	x2 = (rectObject.x + start_map.x + W_Laser) / TILE_SIZE;
	y1 = (rectObject.y + start_map.y + plus_y) / TILE_SIZE;
	y2 = (rectObject.y + start_map.y + plus_y + H_Laser) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (plus_y < 0) {
			if (map_data.tile[y1][x1] == STATE_MONEY || map_data.tile[y1][x2] == STATE_MONEY||
				map_data.tile[y1][x1] == STATE_AID || map_data.tile[y1][x2] == STATE_AID) { ; }
			else if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0) {
				plus_y = 0;
				is_move = false;
				setRectObject(0, 0, 0, 0);
			}
		}

		else if (plus_y > 0) {
			if (map_data.tile[y2][x1] == STATE_MONEY || map_data.tile[y2][x2] == STATE_MONEY ||
				map_data.tile[y2][x1] == STATE_AID || map_data.tile[y2][x2] == STATE_AID) { ; }
			else if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0) {
				plus_y = 0;
				is_move = false;
				setRectObject(0, 0, 0, 0);
			}
		}
	}
	rectObject.x += plus_x;
	rectObject.y += plus_y;
};
