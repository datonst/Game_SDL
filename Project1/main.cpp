// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "baseObject.h"
#include "tile_map.h"
#include "MainObject.h"

int main(int arc, char* argv[])
{
	SDL_Window* g_window = NULL;
	SDL_Renderer* g_renderer = NULL;
	SDL_Event g_even;

	SDL_CF::initSDL(g_window, g_renderer);
	SDL_Texture* background = SDL_CF::loadTexture("img//background.png", g_renderer);
	SDL_RenderCopy(g_renderer, background, NULL, NULL);


	gameMap tx;
	tx.loadMap("map//map01.dat");
	tx.loadMapTiles(g_renderer);

	MainO human;
	human.loadTextureObject("img//player_right.png", g_renderer);
	human.setRectObject(0,0, 60, 64);

	bool is_quit = false;
	while (!is_quit) {
		SDL_RenderCopy(g_renderer, background, NULL, NULL);
		while (SDL_PollEvent(&g_even) != 0) {
			if (g_even.type == SDL_QUIT) {
				is_quit = true;
			}
			human.move_mainO(g_even, g_renderer);
		}

		Map ga_map = tx.getMap();
		tx.setMap(ga_map);

		human.set_startMap(ga_map.start_x_, ga_map.start_y_);  //load vị trí của điểm bắt đầu của map vào human để xử lý.
		human.Renderer_mainO(tx.getMap(), g_renderer);  // xử lý map và nhân vật đồng thời load image nhân vật.


		tx.set_startMap_XY(human.get_startMap().x, human.get_startMap().y); // set lại vị trí sau khi thay đổi của điểm bắt đầu của map vào tile_map;
		tx.drawTiles(g_renderer); 

		SDL_RenderPresent(g_renderer);
	}

	SDL_CF::quitSDL(g_window, g_renderer);
	SDL_DestroyTexture(background);
	background = NULL;

	return 0;
}
#undef main

