#include "baseObject.h"
#include "tile_map.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include"Text.h"
#undef main
int main(int arc, const char* argv[])
{
	int COLOR_KEY_R = 167;
	int COLOR_KEY_G = 175;
	int COLOR_KEY_B = 180;
	SDL_Window* g_window = NULL;
	SDL_Renderer* g_renderer = NULL;
	SDL_Event g_even;
	ImpTimer fps_time;


	SDL_CF::initSDL(g_window, g_renderer);
	if (TTF_Init() == -1) return 0;
	SDL_Texture* background = SDL_CF::loadTexture("img//background.png", g_renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
	SDL_RenderCopy(g_renderer, background, NULL, NULL);
	
	//load Text
	Text time_game,text_money;
	time_game.setTimeGame();
	text_money.setMoney();

	//load map
	gameMap tx;
	tx.loadMap("map//map01.dat");
	tx.loadMapTiles(g_renderer);
	

	//load character
	MainO human;
	human.loadTextureObject("img//player_right.png", g_renderer);
	human.setRectObject(0, 0, 60, 64);
	human.set_number_die(100);
	

	//load threat
	std::vector<threatObject*> list_vat_can;
	threatObject* vat_can;
	for (int i = 1; i < 8; i++) {
		vat_can = new threatObject();
		bool t = vat_can->loadTextureObject("img//threat_left.png", g_renderer);
		if (t == NULL) continue;
		vat_can->set_W_H(WIDTH_THREAT / 8, HEIGTH_THREAT);
		vat_can->set_X_Y(1500 * i - 840, 100);
		vat_can->set_dan_threat(g_renderer);
		list_vat_can.push_back(vat_can);
	}

	//load explosion
	Explosion exp;
	bool t_exp=exp.loadTextureObject("img//exp3.png", g_renderer);


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

		//renderer text
		if (time_game.renderTimeGame(g_window, g_renderer, background)) return 0;
		text_money.renderMoney(human.get_money(), g_renderer);

		//process human and tile_map
		Map ga_map = tx.getMap();
		tx.setMap(ga_map);

		human.set_startMap(ga_map.start_x_, ga_map.start_y_);  //load vị trí của điểm bắt đầu của map vào human để xử lý.
		human.Renderer_mainO(ga_map, g_renderer);  // xử lý map và nhân vật đồng thời load image nhân vật.
		if (human.check_run_over(g_window, g_renderer, background)) return 0;

		tx.setMap(ga_map);
		tx.set_startMap_XY(human.get_startMap().x, human.get_startMap().y); // set lại vị trí sau khi thay đổi của điểm bắt đầu của map vào tile_map;
		tx.drawTiles(g_renderer);


		//check threat_object with main_object
		for (int i = 0; i < list_vat_can.size(); i++) {
			list_vat_can.at(i)->set_startMap(ga_map.start_x_, ga_map.start_y_);
			list_vat_can.at(i)->Renderer_threatO(ga_map, g_renderer);
			//check can_can crash human
			if (SDL_CF::is_crash(list_vat_can.at(i)->getRectObject(), human.getRectObject()) == true) {
				if (human.crash_object(g_window, g_renderer, background)) return 0;
				exp.getRect_x_y_explosion(list_vat_can.at(i)->getRectObject().x, list_vat_can.at(i)->getRectObject().y);
				exp.renderExplosion(g_renderer);
				delete list_vat_can.at(i);
				list_vat_can.at(i) = NULL;
				list_vat_can.erase(list_vat_can.begin() + i);
			}
			//check vat_can_amo to human
			if (SDL_CF::is_crash(list_vat_can.at(i)->dan_T_one()->getRectObject(), human.getRectObject()) == true){
				if (human.crash_object(g_window, g_renderer, background)) return 0;
				list_vat_can.at(i)->dan_T_one()->setRectObject(0, 0, 0, 0);
			}
			// check human_amo to vat_can
			for (int j = 0; j < human.GetlistAmop().size(); j++) {   
				if(list_vat_can.size() == 0) break;
				if (SDL_CF::is_crash(list_vat_can.at(i)->getRectObject(), human.GetlistAmop().at(j)->getRectObject())) {
					if (t_exp != NULL) {
						exp.getRect_x_y_explosion(list_vat_can.at(i)->getRectObject().x, list_vat_can.at(i)->getRectObject().y);
						exp.renderExplosion(g_renderer);
					}
					human.delete_amo_object(j);
					delete list_vat_can.at(i);
					list_vat_can.at(i) = NULL;
					list_vat_can.erase(list_vat_can.begin() + i);
				}
			}
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
