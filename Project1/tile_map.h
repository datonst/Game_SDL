#pragma once

#ifndef TILE_MAP_H
#define TILE_MAP_H
#include "baseObject.h"
#define TILE_SIZE 64
#define STATE_MONEY 7
static const int MAX_MAP_X = 206;
static const int MAX_MAP_Y = 10;
static const int MAX_TILES = 23;

class TileMap : public baseObject {
public:
	TileMap() { ; };
	~TileMap() { ; };
};
struct start {
	int x;
	int y;
};

struct Map
{
	int start_x_;
	int start_y_;
	int max_x_;
	int max_y_;
	int tile[MAX_MAP_Y][MAX_MAP_X];  // MAX_MAP_Y = 10, MAX_MAP_X = 400 -> Save array of tile_map
	const char* file_name_;
};



class gameMap {
private:
	Map game_map_;
	TileMap tile_map[MAX_TILES];
public:
	gameMap();
	~gameMap();

	void loadMap(const std::string name);
	void loadMapTiles(SDL_Renderer* screen);
	void drawTiles(SDL_Renderer* screen);
	Map getMap()  { return game_map_; }
	void setMap(const Map& gMap) { game_map_ = gMap; }
	void set_startMap_XY(const int& x, const int& y) { game_map_.start_x_ = x; game_map_.start_y_ = y; };
};


#endif