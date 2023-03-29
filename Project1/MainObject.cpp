#include "MainObject.h"
#include"tile_map.h"
MainO::MainO() {
	length_frame = 8;
	WIDTH_FRAME = 480;
	HEIGHT_FRAME = 64;
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
	player_images.left = "img//dinosaur_left.png";
	player_images.right = "img//dinosaur_right.png";
	player_images.jump_left = "img//dinosaur_jump_left.png";
	player_images.jump_right = "img//dinosaur_jump_right.png";
};

void  MainO::set_clip() {
	for (int i = 0; i < length_frame; i++) {
		clip[i].x = i * WIDTH_FRAME / length_frame;
		clip[i].y = 0;
		clip[i].w = WIDTH_FRAME / length_frame;
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

void MainO::set_number_die(int const& x, SDL_Renderer* g_renderer) {
	number_die = x;
	for (int i = 0; i < x; i++) {
		baseObject* heart_ = new baseObject();
		heart_->setColorKey(255, 255, 255);
		heart_->loadTextureObject("img//heart.png", g_renderer);
		heart_->setRectObject(i * 40, 0, 35, 35);
		heart.push_back(heart_);
		heart_ = NULL;
	}
}

void MainO::move_mainO(SDL_Event &event, SDL_Renderer* renderer_mainO, Audio& audio_game) {
	
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
			loadTextureObject(player_images.left, renderer_mainO);
			break;
		case SDLK_RIGHT:
			dan_left = false;
			check.right = false;
			clip_mainO.x = 0;
			clip_chay = false;
			plus_x = 0;
			loadTextureObject(player_images.right, renderer_mainO);
			break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		bool dan_sound_left = true;
		Amop* dan = new Amop();
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
		{
			dan->set_W_H(W_Laser, H_Laser);
			dan->loadTextureObject("img//player_bullet.png", renderer_mainO);
			dan_sound_left = true;
			break;
			
		}
		case SDL_BUTTON_RIGHT:
		{
			dan->set_W_H(W_Sphere, H_Sphere);
			dan->loadTextureObject("img//player_bullet1.png", renderer_mainO);
			dan_sound_left = false;
			break;
			
		}
		}
		dan->set_is_move(true);
		dan->left_or_right(dan_left);
		int dan_locate_x = 0;
		if (dan_left == true) dan_locate_x = -6;
		else dan_locate_x = 10;
		dan->set_X_Y(this->rectObject.x +dan_locate_x , this->rectObject.y- WIDTH_FRAME/24+40);
		dan->set_startMap_amo(start_map.x, start_map.y);
		p_amo.push_back(dan);
		if (dan_sound_left == true) {
			audio_game.playSoundAmoLeft();
		}
		else audio_game.playSoundAmoRight();
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		;
	}
	
	UpdateImage(renderer_mainO);
};


void MainO::Renderer_mainO(Map&  map_data,SDL_Renderer* renderer_mainO, Audio& audio_game) {
	if (number_die <= 0) return;
	change_map(map_data, renderer_mainO,audio_game);
	ShowAmo(map_data, renderer_mainO);
	if (come_back_time != 0) return;    // When drop pause load image;
	if (clip_chay == true) {
		clip_mainO = clip[index];
		index++;
		if (index >= length_frame) index = 0;
	}
	renderObject(renderer_mainO, &clip_mainO);
};


void MainO::UpdateImage(SDL_Renderer* renderer_mainO) {
	bool ret = false;
	if (check.right == true) {
		if (check.up == true) ret = loadTextureObject(player_images.jump_right, renderer_mainO);
		else ret = loadTextureObject(player_images.right, renderer_mainO);
	}
	else if (check.left == true) {
		if (check.up == true) ret = loadTextureObject(player_images.jump_left, renderer_mainO);
		else ret = loadTextureObject(player_images.left, renderer_mainO);
	}
}


void MainO::change_map(Map& map_data, SDL_Renderer* g_renderer, Audio& audio_game){
	int w_frame = WIDTH_FRAME / length_frame;
	int h_frame = HEIGHT_FRAME;
	if (come_back_time >0) {
		come_back_time -= 2;
		return;
	}
	plus_y += RUN_Y;
	int w_min = w_frame < TILE_SIZE ? w_frame : TILE_SIZE;
	int h_min = h_frame < TILE_SIZE ? h_frame : TILE_SIZE;



	//check horizontal
	int x1 = (rectObject.x + start_map.x + plus_x) / TILE_SIZE;
	int x2 = (rectObject.x + start_map.x + plus_x + w_frame) / TILE_SIZE;
	int y1 = (rectObject.y+ start_map.y ) / TILE_SIZE;
	int y2 = (rectObject.y+ start_map.y + h_min) / TILE_SIZE;

	if (check.up == true && on_ground == true) {
		plus_y += -RUN_Y * 20;
		check.up = false;
		on_ground = false;
	}
	else plus_y += RUN_Y;



	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) 
	{

		if (plus_x>0) {
			if (map_data.tile[y1][x2] == STATE_MONEY) { 
				map_data.tile[y1][x2] = 0; 
				gain_money++; 
				audio_game.playSoundCollectMoney();
			}
			else if (map_data.tile[y1][x2] == STATE_AID) {
				map_data.tile[y1][x2] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
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
					audio_game.playSoundBomb();
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y2][x2] == STATE_MONEY) { 
				map_data.tile[y2][x2] = 0;
				gain_money++;
				audio_game.playSoundCollectMoney();

			}
			else if (map_data.tile[y2][x2] == STATE_AID) {
				map_data.tile[y2][x2] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
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
					audio_game.playSoundBomb();
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
			if (map_data.tile[y1][x1] == STATE_MONEY) { 
				map_data.tile[y1][x1] = 0;
				gain_money++;
				audio_game.playSoundCollectMoney();
			}
			else if (map_data.tile[y1][x1] == STATE_AID) {
				map_data.tile[y1][x1] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
			}
			else if (map_data.tile[y1][x1] == STATE_BOMB) {
				number_die--;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					audio_game.playSoundBomb();
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y2][x1] == STATE_MONEY) { 
				map_data.tile[y2][x1] = 0;
				gain_money++;
				audio_game.playSoundCollectMoney();
			}
			else if (map_data.tile[y2][x1] == STATE_AID) {
				map_data.tile[y2][x1] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
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
					audio_game.playSoundBomb();
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
			if (map_data.tile[y1][x1] == STATE_MONEY) { 
				map_data.tile[y1][x1] = 0;
				gain_money++;
				audio_game.playSoundCollectMoney();
			}
			else if (map_data.tile[y1][x1] == STATE_AID) {
				map_data.tile[y1][x1] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
			}
			else if (map_data.tile[y1][x1] == STATE_BOMB) {
				map_data.tile[y1][x1] = 0;
				delete  heart[heart.size() - 1];
				heart[heart.size() - 1] = NULL;
				heart.pop_back();
				bool t_exp = exp.loadTextureObject("img//exp3.png", g_renderer);
				if (t_exp != NULL) {
					exp.getRect_x_y_explosion(rectObject.x, rectObject.y);
					audio_game.playSoundBomb();
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;
			}
			if (map_data.tile[y1][x2] == STATE_MONEY) {
				map_data.tile[y1][x2] = 0;
				gain_money++;
				audio_game.playSoundCollectMoney();
			}
			else if (map_data.tile[y1][x2] == STATE_AID) {
				map_data.tile[y1][x2] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
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
					audio_game.playSoundBomb();
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
			if (map_data.tile[y2][x1] == STATE_MONEY) { 
				map_data.tile[y2][x1] = 0; 
				gain_money++;
				audio_game.playSoundCollectMoney();
			}
			else if (map_data.tile[y2][x1] == STATE_AID) {
				map_data.tile[y2][x1] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
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
					audio_game.playSoundBomb();
					exp.renderExplosion(g_renderer);
				}
				if (number_die <= 0) return;
				come_back_time = 60;
				rectObject.x -= TILE_SIZE;
				rectObject.y = 0;

			}
			if (map_data.tile[y2][x2] == STATE_MONEY) { 
				map_data.tile[y2][x2] = 0; 
				gain_money++;
				audio_game.playSoundCollectMoney();
			}
			else if (map_data.tile[y2][x2] == STATE_AID) {
				map_data.tile[y2][x2] = 0;
				insertHeart(g_renderer);
				audio_game.playSoundAddHeart();
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
					audio_game.playSoundBomb();
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
	runMap(map_data,audio_game);
	if (rectObject.y < 0) {
		rectObject.y = 0;
		plus_y += RUN_Y;
	}
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


void MainO::runMap(const Map& map_data, Audio& audio_game) {
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

	if (start_map.x + SDL_CF::SCREEN_WIDTH >= map_data.max_x_ && end_round==false) {
		start_map.x = map_data.max_x_ - SDL_CF::SCREEN_WIDTH;
		end_round = true;
		if (audio_game.setMusicWinner() == false) return;
	}
}


void MainO :: ShowAmo(Map& map_data,SDL_Renderer* renderer_mainO) {
	for (int i = 0; i < p_amo.size(); i++) {
		Amop* doc = p_amo.at(i);
		if (doc == NULL) continue;
		doc->Handle_MM(SDL_CF::SCREEN_WIDTH, SDL_CF::SCREEN_HEIGHT);
		doc->check_map_amo(map_data);
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


bool MainO::check_run_over(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, Audio& audio_game) {
	if (number_die <= 0 && rectObject.x>0) {
		bool ret_game_over = Menu::game_over(g_renderer,audio_game);
		if (ret_game_over == false) return false;
		SDL_RenderPresent(g_renderer);
		int ret_menu = Menu::showMenuStart(g_renderer, background,audio_game);
		if (ret_menu == 1) {
			return true;
		}
		else if (ret_menu == 2) dinosaur(g_renderer);
		else if (ret_menu == 3) wolf(g_renderer);
		rectObject.x = 0;
		rectObject.y = 0;
	}
	if (end_round == true) {

		winner_object.loadTextureObject("img//you_win.png", g_renderer);
		winner_object.setRectObject(300, 100, 765, 331);
		winner_object.renderObject(g_renderer);
	}
	return false;
}

bool MainO::crash_object_over(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, Audio& audio_game) {
	number_die--;
	delete  heart[heart.size() - 1];
	heart[heart.size() - 1] = NULL;
	heart.pop_back();
	if (check_run_over(g_window, g_renderer, background,audio_game)) return true;
	if (number_die > 0) {
		come_back_time = 60;
		rectObject.x -= TILE_SIZE;
		rectObject.y = 0;
	}
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


void MainO::resetHuman(SDL_Renderer* g_renderer) {
	rectObject.x = 0;
	rectObject.y = 0;
	loadTextureObject(player_images.right, g_renderer);
	gain_money = 0;
	score = 0;
	setRectObject(0, 0, WIDTH_FRAME/length_frame, HEIGHT_FRAME);
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
	set_number_die(3, g_renderer);
}


void MainO::change_player(const std::string& l, const std::string& r, const std::string& j_l, const std::string& j_r) {
	player_images.left = l;
	player_images.left = r;
	player_images.jump_left = j_l;
	player_images.jump_right = j_r;
}

void MainO::dinosaur(SDL_Renderer* g_renderer) {
	index = 0;
	WIDTH_FRAME = 480;
	HEIGHT_FRAME = 64;
	length_frame = 8;
	set_clip();
	player_images.left = "img//dinosaur_left.png";
	player_images.right = "img//dinosaur_right.png";
	player_images.jump_left = "img//dinosaur_jump_left.png";
	player_images.jump_right = "img//dinosaur_jump_right.png";
	loadTextureObject(player_images.right, g_renderer);
}

void MainO::wolf(SDL_Renderer* g_renderer) {
	index = 0;
	WIDTH_FRAME = 301;
	HEIGHT_FRAME = 60;
	length_frame = 5;
	set_clip();
	player_images.left = "img//wolf_left.png";
	player_images.right = "img//wolf_right.png";
	player_images.jump_left = "img//wolf_jump_left.png";
	player_images.jump_right = "img//wolf_jump_right.png";
	loadTextureObject(player_images.right, g_renderer);
}
