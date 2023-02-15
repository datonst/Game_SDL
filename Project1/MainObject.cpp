#include "MainObject.h"
#include"tile_map.h"
MainO::MainO() {
	clip_mainO.x = 0;
	clip_mainO.y = 0;
	clip_mainO.w= 60;
	clip_mainO.h = 64;
	clip_chay = false;
	plus_x = 0;
	plus_y = RUN_Y;
	index = 0;
	set_clip();
	check.down = false;
	check.up = false;
	check.right = false;
	check.left = false;
};

void  MainO::set_clip() {
	for (int i = 0; i < 8; i++) {
		clip[i].x = i * WIDTH_FRAME / 8;
		clip[i].y = 0;
		clip[i].w = 60;
		clip[i].h = 64;
	}
}

MainO::~MainO() { ; };


void MainO::move_mainO(SDL_Event event, SDL_Renderer* renderer_mainO) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_DOWN:
			check.down = true;
			check.up = false;
			plus_y = abs(RUN_Y);
			break;
		case SDLK_UP:
			check.up = true;
			check.down = false;
			plus_y = -abs(RUN_Y);
			break;

		case SDLK_LEFT:
			check.left = true;
			check.right = false;
			clip_chay = true;
			plus_x = -abs(RUN_X);
			break;
		case SDLK_RIGHT:
			check.right= true;
			check.left = false;
			clip_chay = true;
			plus_x = abs(RUN_X);
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym) {
		case SDLK_DOWN:
			check.down = false;
			plus_y = 0;
			break;
		case SDLK_UP:
			check.up = false;
			plus_y = 0;
			break;
		case SDLK_LEFT:
			check.left = false;
			clip_mainO.x = 0;
			clip_chay = false;
			plus_x = 0;
			loadTextureObject("img//player_left.png", renderer_mainO);
			break;
		case SDLK_RIGHT:
			check.right = false;
			clip_mainO.x = 0;
			clip_chay = false;
			plus_x = 0;
			loadTextureObject("img//player_right.png", renderer_mainO);
			break;
		}
	}
	UpdateImage(renderer_mainO);
};


void MainO::Renderer_mainO(const Map&  map_data,SDL_Renderer* renderer_mainO) {
	check_map(map_data);
	if (clip_chay == true) {
		clip_mainO = clip[index];
		index++;
		if (index >= 8) index = 0;
	}
	renderObject(renderer_mainO, &clip_mainO);
};


void MainO::UpdateImage(SDL_Renderer* renderer_mainO) {
	bool ret = false;
	if (check.right == true) {
		if(check.up==true) ret=loadTextureObject("img//jum_right.png", renderer_mainO);
		else ret = loadTextureObject("img//player_right.png", renderer_mainO);
	}
	else if(check.left == true) {
		if (check.up == true) ret = loadTextureObject("img//jum_left.png", renderer_mainO);
		else ret = loadTextureObject("img//player_left.png", renderer_mainO);
	}
}


void MainO::check_map(const Map& map_data){
	plus_y = RUN_Y;
	int w_min = w_frame < TILE_SIZE ? w_frame : TILE_SIZE;
	int h_min = h_frame < TILE_SIZE ? h_frame : TILE_SIZE;



	//check horizontal
	int x1=(rectObject.x+ plus_x)/TILE_SIZE;
	int x2 = (rectObject.x + plus_x + w_frame -1) / TILE_SIZE;
	int y1 = (rectObject.y) / TILE_SIZE;
	int y2 = (rectObject.y + h_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) 
	{
		if (plus_x>0) {
			if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0) {
				check.right = false;
				plus_x = 0;
			}
		}
		else if (plus_x < 0) {
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0) {
				check.left = false;
				plus_x = 0;
			}
		}
	}

	//check vertical
	x1 = (rectObject.x) / TILE_SIZE;
	x2 = (rectObject.x + w_min - 1) / TILE_SIZE;
	y1 = (rectObject.y+ plus_y) / TILE_SIZE;
	y2 = (rectObject.y + plus_y + h_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (plus_y<0) {
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0) {
				check.up = false;
				plus_y = 0;
			}
		}

		else if (plus_y >0) {
			if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0) {
				check.down = false;
				plus_y = 0;
			}
		}
	}

	rectObject.x += plus_x;
	rectObject.y += plus_y;
}
