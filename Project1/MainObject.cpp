#include "MainObject.h"
#include"tile_map.h"
MainO::MainO() {
	clip_mainO.x = 0;
	clip_mainO.y = 0;
	clip_mainO.w= WIDTH_FRAME/8;
	clip_mainO.h = HEIGHT_FRAME;
	clip_chay = false;
	plus_x = 0;
	plus_y = RUN_Y;
	index = 0;
	set_clip();
	check.down = false;
	check.up = false;
	check.right = false;
	check.left = false;
	start_map.x = 0;
	start_map.y = 0;
	left_mid = false;
	on_ground = false;
	come_back_time = 0;
	dan_left = false;
	COLOR_KEY_R = 255;
	COLOR_KEY_G = 255;
	COLOR_KEY_B = 255;
	number_die=1;
	gain_money = 0;
	end_round = false;
	score = 0;
};

void  MainO::set_clip() {
	for (int i = 0; i < 8; i++) {
		clip[i].x = i * WIDTH_FRAME / 8;
		clip[i].y = 0;
		clip[i].w = WIDTH_FRAME / 8;
		clip[i].h = HEIGHT_FRAME;
	}
}

MainO::~MainO() {
	for (int i = 0; i < heart.size(); i++) {
		delete heart[i];
		heart[i] = NULL;
	}
	heart.clear();
	for (int i = 0; i < p_amo.size(); i++) {
		delete p_amo[i];
		p_amo[i] = NULL;
	}
	p_amo.clear();
};


void MainO::move_mainO(SDL_Event &event, SDL_Renderer* renderer_mainO) {
	
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
			dan_left = true;
			check.left = true;
			check.right = false;
			clip_chay = true;
			plus_x = -abs(RUN_X);
			break;
		case SDLK_RIGHT:
			dan_left = false;
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
			dan_left = true;
			check.left = false;
			clip_mainO.x = 0;
			clip_chay = false;
			plus_x = 0;
			loadTextureObject("img//player_left.png", renderer_mainO);
			break;
		case SDLK_RIGHT:
			dan_left = false;
			check.right = false;
			clip_mainO.x = 0;
			clip_chay = false;
			plus_x = 0;
			loadTextureObject("img//player_right.png", renderer_mainO);
			break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		Amop* dan = new Amop();
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
		{
			dan->set_W_H(W_Laser, H_Laser);
			dan->loadTextureObject("img//player_bullet.png", renderer_mainO);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			dan->set_W_H(W_Sphere, H_Sphere);
			dan->loadTextureObject("img//player_bullet1.png", renderer_mainO);
			break;
		}
		}
		dan->set_is_move(true);
		dan->left_or_right(dan_left);
		int dan_locate_x = 0;
		if (dan_left == true) dan_locate_x = -6;
		else dan_locate_x = 60;
		dan->set_X_Y(this->rectObject.x +dan_locate_x , this->rectObject.y+20);
		dan->set_startMap_amo(start_map.x, start_map.y);
		p_amo.push_back(dan);
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		;
	}
	
	UpdateImage(renderer_mainO);
};


void MainO::Renderer_mainO(Map&  map_data,SDL_Renderer* renderer_mainO) {
	if (number_die <= 0) return;
	change_map(map_data, renderer_mainO);
	ShowAmo(map_data, renderer_mainO);
	if (come_back_time != 0) return;    // When drop pause load image;
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
		if (check.up == true) ret = loadTextureObject("img//jum_right.png", renderer_mainO);
		else ret = loadTextureObject("img//player_right.png", renderer_mainO);
	}
	else if (check.left == true) {
		if (check.up == true) ret = loadTextureObject("img//jum_left.png", renderer_mainO);
		else ret = loadTextureObject("img//player_left.png", renderer_mainO);
	}
}


void MainO::change_map(Map& map_data, SDL_Renderer* g_renderer){
	if (come_back_time >0) {
		come_back_time -= 2;
		return;
	}
	plus_y += RUN_Y;
	int w_min = w_frame < TILE_SIZE ? w_frame : TILE_SIZE;
	int h_min = h_frame < TILE_SIZE ? h_frame : TILE_SIZE;



	//check horizontal
	int x1 = (rectObject.x + start_map.x + plus_x) / TILE_SIZE;
	int x2 = (rectObject.x + start_map.x + plus_x + w_frame -1 ) / TILE_SIZE;
	int y1 = (rectObject.y+ start_map.y ) / TILE_SIZE;
	int y2 = (rectObject.y+ start_map.y + h_min -1 ) / TILE_SIZE;

	if (check.up == true && on_ground == true) {
		plus_y += -RUN_Y * 20;
		check.up = false;
		on_ground = false;
	}
	else plus_y += RUN_Y;



	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) 
	{

		if (plus_x>0) {
			if (map_data.tile[y1][x2] == STATE_MONEY) { map_data.tile[y1][x2] = 0; gain_money++; }
			else if (map_data.tile[y1][x2] == STATE_AID) {
				map_data.tile[y1][x2] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y1][x2] == STATE_BOMB) {
				number_die--;
				map_data.tile[y1][x2] = 0;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y2][x2] == STATE_MONEY) { map_data.tile[y2][x2] = 0; gain_money++; }
			else if (map_data.tile[y2][x2] == STATE_AID) {
				map_data.tile[y2][x2] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y2][x2] == STATE_BOMB) {
				number_die--;
				map_data.tile[y2][x2] = 0;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;

				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0) {
				check.right = false;
				plus_x = 0;
			}
		}
		else if (plus_x < 0) {
			if (map_data.tile[y1][x1] == STATE_MONEY) { map_data.tile[y1][x1] = 0; gain_money++; }
			else if (map_data.tile[y1][x1] == STATE_AID) {
				map_data.tile[y1][x1] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y1][x1] == STATE_BOMB) {
				number_die--;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y2][x1] == STATE_MONEY) { map_data.tile[y2][x1] = 0; gain_money++; }
			else if (map_data.tile[y2][x1] == STATE_AID) {
				map_data.tile[y2][x1] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y2][x1] == STATE_BOMB) {
				number_die--;
				map_data.tile[y2][x1] = 0;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0) {
				check.left = false;
				plus_x = 0;

			}
		}
	}

	//check vertical
	x1 = (rectObject.x+ start_map.x) / TILE_SIZE;
	x2 = (rectObject.x + start_map.x + w_min ) / TILE_SIZE;
	y1 = (rectObject.y+ start_map.y + plus_y) / TILE_SIZE;
	y2 = (rectObject.y + start_map.y + plus_y + h_frame ) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (plus_y<0) {
			if (map_data.tile[y1][x1] == STATE_MONEY) { map_data.tile[y1][x1] = 0; gain_money++;}
			else if (map_data.tile[y1][x1] == STATE_AID) {
				map_data.tile[y1][x1] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y1][x1] == STATE_BOMB) {
				map_data.tile[y1][x1] = 0;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y1][x2] == STATE_MONEY) { map_data.tile[y1][x2] = 0; gain_money++;}
			else if (map_data.tile[y1][x2] == STATE_AID) {
				map_data.tile[y1][x2] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y1][x2] == STATE_BOMB) {
				number_die--;
				map_data.tile[y1][x2] = 0;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}

			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0) {
				check.up = false;
				plus_y = 0;
				on_ground = true;
			}
		}

		else if (plus_y >0) {
			if (map_data.tile[y2][x1] == STATE_MONEY) { map_data.tile[y2][x1] = 0; gain_money++;}
			else if (map_data.tile[y2][x1] == STATE_AID) {

				map_data.tile[y2][x1] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y2][x1] == STATE_BOMB) {
				number_die--;
				map_data.tile[y2][x1] = 0;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;

			}
			if (map_data.tile[y2][x2] == STATE_MONEY) { map_data.tile[y2][x2] = 0; gain_money++;}
			else if (map_data.tile[y2][x2] == STATE_AID) {
				map_data.tile[y2][x2] = 0;
				insertHeart(g_renderer);
			}
			else if (map_data.tile[y2][x2] == STATE_BOMB) {
				map_data.tile[y2][x2] = 0;
				number_die--;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0) {
				check.down = false;
				plus_y = 0;
				on_ground = true;
			}
		}
	}
	runMap(map_data);
	if (rectObject.y < 0) plus_y += RUN_Y; 
	if (end_round == false) start_map.x += plus_x;
	rectObject.x += plus_x;
	rectObject.y += plus_y;
	if (rectObject.y > map_data.max_y_) {
		number_die--;
		delete  heart[heart.size() - 1];
		heart[heart.size() - 1] = NULL;
		heart.pop_back();
		if (number_die == 0) return;
		come_back_time = 60;
		rectObject.x -= 4 * TILE_SIZE;
		rectObject.y = 0;

	}
	
}


void MainO::runMap(const Map& map_data) {
	if (number_die <= 0) {
		return;
	}
	if (rectObject.x > SDL_CF::SCREEN_WIDTH*9/10) {
		rectObject.x = SDL_CF::SCREEN_WIDTH*9/10;
		return;
	}
	if (rectObject.x < SDL_CF::SCREEN_WIDTH / 3 && left_mid == true && end_round==false) rectObject.x = SDL_CF::SCREEN_WIDTH / 3;
	else if (rectObject.x > 2 * SDL_CF::SCREEN_WIDTH / 3 && start_map.x < map_data.max_x_ - SDL_CF::SCREEN_WIDTH && end_round==false) { rectObject.x = 2 * SDL_CF::SCREEN_WIDTH / 3; left_mid = true; }
	if (start_map.x == 0) {
		left_mid = false;
	}

	if (start_map.x < 0) start_map.x = 0;
	if (rectObject.x < 0) rectObject.x = 0;

	if (start_map.x + SDL_CF::SCREEN_WIDTH >= map_data.max_x_) {
		start_map.x = map_data.max_x_ - SDL_CF::SCREEN_WIDTH;
		end_round = true;
	}
}


void MainO :: ShowAmo(Map& map_data,SDL_Renderer* renderer_mainO) {
	for (int i = 0; i < p_amo.size(); i++) {
		Amop* doc = p_amo.at(i);
		if (doc == NULL) continue;
		doc->check_map_amo(map_data);
		doc->Handle_MM(SDL_CF::SCREEN_WIDTH, SDL_CF::SCREEN_HEIGHT);
		if (doc->get_is_move()) {
			doc->renderObject(renderer_mainO);
		}
		else {
			p_amo.erase(p_amo.begin() + i);
			delete doc;
			doc = NULL;
		}
	}
}

bool MainO::check_run_over(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background) {
	if (number_die <= 0 && rectObject.x>0) {
		bool ret_game_over = Menu::game_over(g_renderer);
		if (ret_game_over == false) return false;
		SDL_RenderPresent(g_renderer);
		bool ret_menu = Menu::showMenu(g_renderer, background);
		if (ret_menu == true) {
			SDL_CF::quitSDL(g_window, g_renderer);
			SDL_DestroyTexture(background);
			background = NULL;
			return true;
		}
		rectObject.x = 0;
		rectObject.y = 0;
	}
	return false;
}

bool MainO::crash_object(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background) {
	number_die--;
	delete  heart[heart.size() - 1];
	heart[heart.size() - 1] = NULL;
	heart.pop_back();
	if (check_run_over(g_window, g_renderer, background)) return true;
	if (number_die <= 0) return true;
	return false;
}

void MainO::renderer_heart(SDL_Renderer* g_renderer) {
	for (auto & x : heart) {
		x->renderObject(g_renderer);
	}
	return;
}

void MainO::insertHeart(SDL_Renderer* g_renderer) {
	number_die++;
	baseObject* heart_ = new baseObject();
	heart_->setColorKey(255, 255, 255);
	heart_->loadTextureObject("img//heart.png", g_renderer);
	heart_->setRectObject(heart.at(heart.size()-1)->getRectObject().x + 40, 0, 35, 35);
	heart.push_back(heart_);
}


void MainO::resetHuman() {
	gain_money = 0;
	score = 0;
	rectObject.x = 0;
	rectObject.y = 0;
	start_map.x = 0;
	start_map.y = 0;
	plus_x = 0;
	end_round = false;
	left_mid = false;
	clip_chay = false;
	index = 0;
	check.left = false;
	check.right = true;

	for (int i = 0; i < heart.size(); i++) {
		delete heart[i];
		heart[i] = NULL;
	}
	heart.clear();
	
}