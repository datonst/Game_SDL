#include "baseObject.h"
#include "tile_map.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"
int main(int arc, char* argv[])
{
	int COLOR_KEY_R = 167;
	int COLOR_KEY_G = 175;
	int COLOR_KEY_B = 180;	
	SDL_Window* g_window = NULL;
	SDL_Renderer* g_renderer = NULL;
	SDL_Event g_even;
	ImpTimer fps_time;


	SDL_CF::initSDL(g_window, g_renderer);
	SDL_Texture* background = SDL_CF::loadTexture("img//background.png", g_renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
	SDL_RenderCopy(g_renderer, background, NULL, NULL);


	gameMap tx;
	tx.loadMap("map//map01.dat");
	tx.loadMapTiles(g_renderer);

	MainO human;
	human.loadTextureObject("img//player_right.png", g_renderer);
	human.setRectObject(0, 0, 60, 64);

	std::vector<threatObject*> list_vat_can;
	threatObject* vat_can;
	for (int i = 1; i <8; i++) {
		vat_can = new threatObject();
		bool t = vat_can->loadTextureObject("img//threat_left.png", g_renderer);
		if (t == NULL) continue;
		vat_can->set_W_H(WIDTH_THREAT / 8, HEIGTH_THREAT);
		vat_can->set_X_Y(1500 * i - 840, 100);
		vat_can->set_dan_threat(g_renderer);
		list_vat_can.push_back(vat_can);
	}



	bool is_quit = false;
	while (!is_quit) {
		fps_time.start();
		SDL_RenderCopy(g_renderer, background, NULL, NULL);
		while (SDL_PollEvent(&g_even) != 0) {
			if (g_even.type == SDL_QUIT) {
				is_quit = true;
			}
			human.move_mainO(g_even, g_renderer);
		}


		//process human and tile_map
		Map ga_map = tx.getMap();
		tx.setMap(ga_map);

		human.set_startMap(ga_map.start_x_, ga_map.start_y_);  //load vị trí của điểm bắt đầu của map vào human để xử lý.
		human.Renderer_mainO(ga_map, g_renderer);  // xử lý map và nhân vật đồng thời load image nhân vật.


		tx.setMap(ga_map);
		tx.set_startMap_XY(human.get_startMap().x, human.get_startMap().y); // set lại vị trí sau khi thay đổi của điểm bắt đầu của map vào tile_map;
		tx.drawTiles(g_renderer);


		for (int i = 0; i < list_vat_can.size(); i++) {
			list_vat_can.at(i)->set_startMap(ga_map.start_x_, ga_map.start_y_);
			list_vat_can.at(i)->Handle_M_T(0, 0);
			if (list_vat_can.at(i)->dan_T_list().at(0)->getRectObject().x >0 && human.getRectObject().x >= list_vat_can.at(i)->getRectObject().x) {
				list_vat_can.at(i)->set_is_reset(false);
				continue;
			}
			list_vat_can.at(i)->set_is_reset(true);
			baseObject* doc = list_vat_can.at(i)->dan_T_list().at(0);
			doc->renderObject(g_renderer);
			list_vat_can.at(i)->Renderer_threatO(ga_map, g_renderer);
		}

		SDL_RenderPresent(g_renderer);

		//process timer
		int real_timer = fps_time.get_ticks();
		int time_one_frame = 1000 / 25;
		if (real_timer < time_one_frame) {
			int delay = time_one_frame - real_timer;
			if (delay > 0) {
				SDL_Delay(delay);
			}
		}
	}

	SDL_CF::quitSDL(g_window, g_renderer);
	SDL_DestroyTexture(background);
	background = NULL;

	return 0;
}
#undef main