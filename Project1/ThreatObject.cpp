#include "ThreatObject.h"

threatObject::threatObject() {
	come_back_time = 0;
	x_val_T = 0;
	y_val_T = 0;
	rectObject.x = 0;
	rectObject.y =0;
	rectObject.w = 0;
	rectObject.h = 0;
	index = 0;
	clip_threat.x = 0;
	clip_threat.y = 0;
	clip_threat.w = WIDTH_THREAT_BEAR/8;
	clip_threat.h = HEIGTH_THREAT_BEAR;
	start_map.x = 0;
	start_map.y = 0;
	COLOR_KEY_R = 255;
	COLOR_KEY_G = 255;
	COLOR_KEY_B = 255;
	right_threat = 0;
	left_threat = 0;
	plus_x = 0;
	on_ground = false;
	check_go_left = false;
	check_go_right = false;
	plus_dan_threat = 25;
	set_clip();
}
void  threatObject::set_clip() {
	for (int i = 0; i < 8; i++) {
		clip[i].x = i * WIDTH_THREAT_BEAR / 8;
		clip[i].y = 0;
		clip[i].w = WIDTH_THREAT_BEAR / 8;
		clip[i].h = HEIGTH_THREAT_BEAR;
	}
}

threatObject::~threatObject() {
		if (dan_t_one != NULL) { delete dan_t_one; dan_t_one = NULL; }
}


void threatObject::check_map_threat(const Map& map_data) {
	
	if (come_back_time > 0) {
		come_back_time -= 2;
		return;
	}
	plus_y += GRAVITY;
	rectObject.x = x_val_T - start_map.x;
	//check horizontal
	int x1 = (x_val_T + plus_x) / TILE_SIZE;
	int x2 = (x_val_T + plus_x + WIDTH_THREAT_BEAR / 8 - 1) / TILE_SIZE;
	int y1 = (rectObject.y ) / TILE_SIZE;
	int y2 = (rectObject.y+ HEIGTH_THREAT_BEAR - 1) / TILE_SIZE;


	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (plus_x >= 0) {
			if (map_data.tile[y1][x2] == STATE_MONEY || map_data.tile[y2][x2] == STATE_MONEY ||
				map_data.tile[y1][x2] == STATE_AID || map_data.tile[y2][x2] == STATE_AID) { ; }
			else if ((map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)) {
				plus_x = 0;
				if (dan_t_one != NULL) {
					dan_t_one->setRectObject(this->rectObject.x + 30, this->rectObject.y, W_Laserr, H_Laserr);
					dan_t_one->left_or_right(true);
				}
				check_go_left = true;
				check_go_right = false;
				on_ground = true;
			}
		}
		if (plus_x <= 0) {
			if (map_data.tile[y1][x1] == STATE_MONEY || map_data.tile[y2][x1] == STATE_MONEY ||
				map_data.tile[y1][x1] == STATE_AID || map_data.tile[y2][x1] == STATE_AID) {  ;}
			else if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0) {
				plus_x = 0;
				if (dan_t_one != NULL) {
					dan_t_one->setRectObject(this->rectObject.x - 30, this->rectObject.y, W_Laserr, H_Laserr);
					dan_t_one->left_or_right(false);
				}
				check_go_left = false;
				check_go_right = true;
				on_ground = true;
			}
		}
	}

	//check vertical
	x1 = (x_val_T) / TILE_SIZE;
	x2 = (x_val_T + WIDTH_THREAT_BEAR / 8) / TILE_SIZE;
	y1 = (rectObject.y  + plus_y) / TILE_SIZE;
	y2 = (rectObject.y  + plus_y + HEIGTH_THREAT_BEAR) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (plus_y < 0) {
			if (map_data.tile[y1][x1] == STATE_MONEY || map_data.tile[y1][x2] == STATE_MONEY||
				map_data.tile[y1][x1] == STATE_AID || map_data.tile[y1][x2] == STATE_AID) { rectObject.y += plus_y; }
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0) {
				plus_y = 0;
				on_ground = true;

			}
			else on_ground = false;
		}

		else if (plus_y > 0) {
			if (map_data.tile[y2][x1] == STATE_MONEY || map_data.tile[y2][x2] == STATE_MONEY ||
				map_data.tile[y2][x1] == STATE_AID || map_data.tile[y2][x2] == STATE_AID) { rectObject.y += plus_y; }
			if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0) {
				plus_y = 0;
				on_ground = true;
			}
			else on_ground = false;
		}
	}
	if (on_ground == false) plus_y += GRAVITY;
	x_val_T += plus_x;
	rectObject.y += plus_y;
	if (rectObject.y > map_data.max_y_) {

	}
	if (rectObject.y > map_data.max_y_) {
		come_back_time = 60;
		rectObject.x -= 4 * TILE_SIZE;
		rectObject.y = 0;
	}
}

void threatObject::move_threat(SDL_Renderer* screen)
{
	if (on_ground == false) {
		plus_x = 0;
		return;
	}

	if (x_val_T < left_threat) { 
		plus_x = SPEED_THREAT; check_go_right = true; check_go_left = false;  
		dan_t_one->setRectObject(this->rectObject.x - 30, this->rectObject.y, W_Laserr, H_Laserr); 
		dan_t_one->left_or_right(false);
	}
	else if (x_val_T > right_threat) {
		plus_x = -SPEED_THREAT; check_go_right = false; check_go_left = true; 
		dan_t_one->setRectObject(this->rectObject.x + 30, this->rectObject.y, W_Laserr, H_Laserr);
		dan_t_one->left_or_right(true);
	}
	if(dan_t_one->getRectObject().x>rectObject.x+RANGE_X*5 || dan_t_one->getRectObject().x < rectObject.x - RANGE_X * 5) dan_t_one->setRectObject(0,0,0,0);


	if (check_go_left== true) {
		loadTextureObject("img//threat_left.png", screen);
		check_go_right = false;
		plus_x = -SPEED_THREAT;
	}
	else {
		loadTextureObject("img//threat_right.png", screen);
		check_go_right = true;
		plus_x = SPEED_THREAT;
	}
}

void threatObject::Renderer_threatO(Map& map_data, SDL_Renderer* renderer_threatO) {
	dan_t_one->set_startMap_amo(start_map.x, start_map.y);
	check_map_threat(map_data);
	dan_t_one->check_map_amo(map_data);
	clip_threat = clip[index];
	index++;
	if (index >= 8) index = 0;
	dan_t_one->renderObject(renderer_threatO);
	move_threat(renderer_threatO);
	renderObject(renderer_threatO, &clip_threat);
}


void threatObject::set_dan_threat(SDL_Renderer* rendererThreat) {
	dan_t_one = new Amop();
	bool load = dan_t_one->loadTextureObject("img//player_bullet.png", rendererThreat);
	if (load == NULL) return;
}



