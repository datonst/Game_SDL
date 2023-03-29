#include "BaseObject.h"
#include "tile_map.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include"Text.h"
#include "Menu.h"
#include "Bottom_Menu.h"
#include"Audio.h"
#undef main
int main()
{
	int COLOR_KEY_R = 167;
	int COLOR_KEY_G = 175;
	int COLOR_KEY_B = 180;
	SDL_Window* g_window = NULL;
	SDL_Renderer* g_renderer = NULL;
	SDL_Event g_even;
	ImpTimer fps_time;
	if (SDL_CF::initSDL(g_window, g_renderer) == false) return 0;;
	if (TTF_Init() == -1) return 0;

	Audio audio_game;
	if (audio_game.setAudio(g_renderer) == false) return 0;
	SDL_Texture* background=NULL;
	int ret_menu = Menu::showMenuStart(g_renderer, background,audio_game);
	if (ret_menu == 1) return 0;
	background = SDL_CF::loadTexture("img//background.png", g_renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
	SDL_RenderCopy(g_renderer, background, NULL, NULL);

	

	Text time_game,text_money,text_score,text_exit;
	time_game.setTimeGame();
	text_money.setMoney(0,g_renderer);
	text_score.setScore(0,g_renderer);
	text_exit.setExit(g_renderer);


	//init map
	gameMap tx;
	
	//init character
	MainO human;
	

	//init threat
	std::vector<threatObject*> list_bear;

	//load explosion
	Explosion exp;
	bool t_exp=exp.loadTextureObject("img//exp3.png", g_renderer);

	//set type character
	if (ret_menu == 2) human.dinosaur(g_renderer);
	else if (ret_menu == 3) human.wolf(g_renderer);

	//init object
	Bottom::bottom_start_menu(g_window, g_renderer, background, human, tx, time_game, list_bear);
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
					if (human.winner() == true) {
						int ret_menu = Menu::showMenuStart(g_renderer, background, audio_game);
						if (ret_menu == 1) {
							return 0;
						}
						else if (ret_menu == 2) human.dinosaur(g_renderer);
						else if (ret_menu == 3) human.wolf(g_renderer);
						Bottom::bottom_start_menu(g_window, g_renderer, background, human, tx, time_game, list_bear);
					}
					else {
						ImpTimer pause;
						pause.start();
						int ret_menu = Menu::showMenu(g_renderer, background, audio_game);
						if (ret_menu == 1) return 0;
						else if (ret_menu == 0) time_game.resumeTime(pause.get_ticks() / 1000);
						else {
							if (ret_menu == 2) { human.dinosaur(g_renderer); }
							else if (ret_menu == 3) human.wolf(g_renderer);
							Bottom::bottom_start_menu(g_window, g_renderer, background, human, tx, time_game, list_bear);
						}
					}
				}
			}
			break;
			case SDL_KEYDOWN:
				if (g_even.key.keysym.sym == SDLK_ESCAPE)
				{
					ImpTimer pause;
					pause.start();
					int ret_menu = Menu::showMenu(g_renderer, background,audio_game);
					if (ret_menu == 1) return 0;
					else if (ret_menu == 0) time_game.resumeTime(pause.get_ticks() / 1000);
					else {
						if (ret_menu == 2) { human.dinosaur(g_renderer); }
						else if (ret_menu == 3) human.wolf(g_renderer);
						Bottom::bottom_start_menu(g_window, g_renderer, background, human, tx, time_game, list_bear);
					}
				}
			default:
				break;
			}
			human.move_mainO(g_even, g_renderer,audio_game);
		}
		
		//check time
		int check_time = time_game.renderTimeGame(g_window, g_renderer, background,audio_game,human.winner());
		if (check_time == 1) break;
		else if (check_time == 2) human.dinosaur(g_renderer);
		else if (check_time == 3) human.wolf(g_renderer);

		//renderer text
		text_money.changeMoney(human.get_money(), g_renderer);
		text_score.changeScore(human.get_score(), g_renderer);
		

		//process human and tile_map
		Map ga_map = tx.getMap();
		tx.setMap(ga_map);

		human.set_startMap(ga_map.start_x_, ga_map.start_y_);  //load vị trí của điểm bắt đầu của map vào human để xử lý.
		human.Renderer_mainO(ga_map, g_renderer,audio_game);  // xử lý map và nhân vật đồng thời load image nhân vật.
		

		tx.setMap(ga_map);
		tx.set_startMap_XY(human.get_startMap().x, human.get_startMap().y); // set lại vị trí sau khi thay đổi của điểm bắt đầu của map vào tile_map;
		tx.drawTiles(g_renderer);
		//reset Start
		if (human.check_run_over(g_window, g_renderer, background,audio_game)) break;
		if (human.get_number_die() <= 0 || time_game.get_val_time() <= 0) {
			Bottom::bottom_start_menu(g_window, g_renderer, background, human, tx, time_game, list_bear);
			continue;
		}
		//check threat_object with main_object
		if (Crash::Crash_Object(g_window, g_renderer, background, human, ga_map, exp, list_bear,audio_game)) break;
		human.renderer_heart(g_renderer);
		text_exit.renderText(g_renderer);
		SDL_RenderPresent(g_renderer);

		if (human.get_number_die() <= 0 || time_game.get_val_time() <= 0) {
			Bottom::bottom_start_menu(g_window, g_renderer, background, human, tx, time_game, list_bear);
			continue;
		}
		//process timer
		fps_time.fps();
	}

	SDL_CF::quitSDL(g_window, g_renderer);
	SDL_DestroyTexture(background);
	background = NULL;

	return 0;
}
