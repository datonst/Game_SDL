// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "baseObject.h"
#include "tile_map.h"
#include "MainObject.h"

int main(int arc, char* argv[])
{

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
		tx.drawTiles(g_renderer);
		human.Renderer_mainO(tx.getMap(), g_renderer);
		SDL_RenderPresent(g_renderer);
	}

	SDL_CF::quitSDL(g_window, g_renderer);
	SDL_DestroyTexture(background);
	background = NULL;

	return 0;
}
#undef main

