
#include "tile_map.h"
#include <iostream>
#include <fstream>
gameMap::gameMap()
{
    ;
}

gameMap::~gameMap()
{
    ;
}


void gameMap::loadMap( const std::string name)
{
    std::ifstream sa(name);

    game_map_.max_x_ = game_map_.max_y_ = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            sa>>game_map_.tile[i][j];
            if (game_map_.tile[i][j] > 0)
            {
                if (j > game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }

                if (i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
    }
    sa.close();

    game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

    game_map_.start_x_ = game_map_.start_y_ = 0;

    game_map_.file_name_ = name.c_str();
}

void gameMap::loadMapTiles(SDL_Renderer* screen)
{

    for (int i = 0; i < MAX_TILES; i++)
    {
        const std::string filename = "map//"+std::to_string(i) + ".png";
        std:: ifstream docfile (filename);
        if (!docfile) continue;
        tile_map[i].loadTextureObject(filename, screen);
    }
}

void gameMap::drawTiles(SDL_Renderer* des)
{
    int map_x = 0;
    int x1 = 0;
    int x2 = 0;

    int map_y = 0;
    int y1 = 0;
    int y2 = 0;

    //map_x = game_map_.start_x_/TILE_SIZE;
    x1 = (game_map_.start_x_ % TILE_SIZE) * (-1) ;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    //map_y = game_map_.start_y_/TILE_SIZE;
    y1 = (game_map_.start_y_ % TILE_SIZE) * (-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    
    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_ / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            if (game_map_.tile[map_y][map_x] != 0)
            {
                tile_map[game_map_.tile[map_y][map_x]].setRectObject(j, i, TILE_SIZE, TILE_SIZE);
                tile_map[game_map_.tile[map_y][map_x]].renderObject(des);
            }
            map_x++;
        }
        map_y++;
    }

}