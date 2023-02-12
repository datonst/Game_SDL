// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "baseObject.h"
#include "tile_map.h"
int main(int arc, char* argv[])
{
	SDL_CF::initSDL(g_window, g_renderer);
	SDL_Texture* background = SDL_CF::loadTexture("background.png", g_renderer);
	SDL_RenderCopy(g_renderer, background, NULL, NULL);
	SDL_RenderPresent(g_renderer);


	gameMap tx;
	tx.loadMap("map//map01.dat");
	tx.loadMapTiles(g_renderer);

	bool is_quit = false;
	while (!is_quit) {
		while (SDL_PollEvent(&g_even) != 0) {
			if (g_even.type == SDL_QUIT) {
				is_quit = true;
			}
		}
		Map ga_map = tx.getMap();
		tx.setMap(ga_map);
		tx.drawTiles(g_renderer);
		SDL_RenderPresent(g_renderer);


	}

	SDL_CF::quitSDL(g_window, g_renderer);
	SDL_DestroyTexture(background);
	background = NULL;

	return 0;
}
#undef main

