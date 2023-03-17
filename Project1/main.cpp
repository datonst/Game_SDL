#include "baseObject.h"
#include "tile_map.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include"Text.h"
#include "Menu.h"
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
	SDL_Texture* background=NULL;
	bool ret_menu = Menu::showMenu(g_renderer, background);
	if (ret_menu == true) return 0;
	background = SDL_CF::loadTexture("img//background.png", g_renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
	SDL_RenderCopy(g_renderer, background, NULL, NULL);

	
	Text time_game,text_money,text_score,text_exit;
	time_game.setTimeGame();
	text_money.setMoney(0,g_renderer);
	text_score.setScore(0,g_renderer);
	text_exit.setExit(g_renderer);


	//load map
	gameMap tx;
	tx.loadMap("map//map01.dat");
	tx.loadMapTiles(g_renderer);
	

	//load character
	MainO human;
	human.loadTextureObject("img//player_right.png", g_renderer);
	human.setRectObject(0, 0, 60, 64);
	human.set_number_die(3,g_renderer);
	

	//load threat
	std::vector<threatObject*> list_bear;
	std::vector<threatObject*> list_bomb;
	Menu::initBear(list_bear, g_renderer);


	//load explosion
	Explosion exp;
	bool t_exp=exp.loadTextureObject("img//exp3.png", g_renderer);


	bool is_quit = false;
	while (!is_quit) {
		fps_time.start();
		SDL_RenderCopy(g_renderer, background, NULL, NULL);
		while (SDL_PollEvent(&g_even) != 0) {
			switch (g_even.type)
			{
			case SDL_QUIT:
				is_quit = true;
				break;
			case SDL_MOUSEMOTION:
			{
				if (Menu::CheckFocusWithRect(g_even.motion.x, g_even.motion.y, text_exit.getRectText()))
				{
					text_exit.setColor(Text::RED_TEXT);
				}
				else
				{
					text_exit.setColor(Text::BLACK_TEXT);
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				if (Menu::CheckFocusWithRect(g_even.motion.x, g_even.motion.y, text_exit.getRectText()))
				{
					bool ret_menu = Menu::showMenu(g_renderer, background);
					if (ret_menu == true) return 0;
				}
			}
			break;
			case SDL_KEYDOWN:
				if (g_even.key.keysym.sym == SDLK_ESCAPE)
				{
					bool ret_menu = Menu::showMenu(g_renderer, background);
					if (ret_menu == true) return 0;
				}
			default:
				break;
			}
			human.move_mainO(g_even, g_renderer);
		}
		
		//renderer text
		if (time_game.renderTimeGame(g_window, g_renderer, background)) return 0;
		text_money.changeMoney(human.get_money(), g_renderer);
		text_score.changeScore(human.get_score(), g_renderer);
		

		if (human.get_number_die() > 0) {

		}
		//process human and tile_map
		Map ga_map = tx.getMap();
		tx.setMap(ga_map);

		human.set_startMap(ga_map.start_x_, ga_map.start_y_);  //load vị trí của điểm bắt đầu của map vào human để xử lý.
		human.Renderer_mainO(ga_map, g_renderer);  // xử lý map và nhân vật đồng thời load image nhân vật.
		

		tx.setMap(ga_map);
		tx.set_startMap_XY(human.get_startMap().x, human.get_startMap().y); // set lại vị trí sau khi thay đổi của điểm bắt đầu của map vào tile_map;
		tx.drawTiles(g_renderer);
		//reset Start
		if (human.check_run_over(g_window, g_renderer, background)) return 0;
		if (human.get_number_die() <= 0 || time_game.get_val_time() <= 0) {
			background = SDL_CF::loadTexture("img//background.png", g_renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
			SDL_RenderCopy(g_renderer, background, NULL, NULL);
			human.resetHuman();
			tx.loadMap("map//map01.dat");
			tx.set_startMap_XY(0, 0);
			human.set_number_die(3, g_renderer);
			time_game.resetTime(SDL_GetTicks() / 1000);
			Menu::initBear(list_bear, g_renderer);
			continue;
		}

		//check threat_object with main_object

		for (int i = 0; i < list_bear.size(); i++) {
			if (list_bear.size() == 0) break;
			list_bear.at(i)->set_startMap(ga_map.start_x_, ga_map.start_y_);
			list_bear.at(i)->Renderer_threatO(ga_map, g_renderer);
			
			//check can_can crash human
			if (SDL_CF::is_crash(list_bear.at(i)->getRectObject(), human.getRectObject()) == true) {
				exp.getRect_x_y_explosion(list_bear.at(i)->getRectObject().x, list_bear.at(i)->getRectObject().y);
				exp.renderExplosion(g_renderer);
				if (human.crash_object(g_window, g_renderer, background)) break;
				delete list_bear.at(i);
				list_bear.at(i) = NULL;
				list_bear.erase(list_bear.begin() + i);
			}
			//check vat_can_amo to human
			if (SDL_CF::is_crash(list_bear.at(i)->dan_T_one()->getRectObject(), human.getRectObject()) == true){
				if (human.crash_object(g_window, g_renderer, background)) break;
				list_bear.at(i)->dan_T_one()->setRectObject(0, 0, 0, 0);
			}
			// check human_amo to vat_can
			for (int j = 0; j < human.GetlistAmop().size(); j++) {   
				if(list_bear.size() == 0) break;
				if (SDL_CF::is_crash(list_bear.at(i)->getRectObject(), human.GetlistAmop().at(j)->getRectObject())) {
					if (t_exp != NULL) {
						exp.getRect_x_y_explosion(list_bear.at(i)->getRectObject().x, list_bear.at(i)->getRectObject().y);
						exp.renderExplosion(g_renderer);
						human.add_score(100);
					}
					human.delete_amo_object(j);
					delete list_bear.at(i);
					list_bear.at(i) = NULL;
					list_bear.erase(list_bear.begin() + i);
				}
			}
		}
		human.renderer_heart(g_renderer);
		text_exit.renderText(g_renderer);
		SDL_RenderPresent(g_renderer);
		if (human.get_number_die() <= 0 || time_game.get_val_time() <= 0) {
			background = SDL_CF::loadTexture("img//background.png", g_renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
			SDL_RenderCopy(g_renderer, background, NULL, NULL);
			human.resetHuman();
			tx.loadMap("map//map01.dat");
			tx.set_startMap_XY(0, 0);
			human.set_number_die(3, g_renderer);
			time_game.resetTime(SDL_GetTicks() / 1000);
			Menu::initBear(list_bear, g_renderer);
			continue;
		}
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
