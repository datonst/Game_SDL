#include "Bottom_Menu.h"
void Bottom::initBear(std::vector<threatObject*>& list_bear, SDL_Renderer* g_renderer) {
	for (int i = 0; i < list_bear.size(); i++) {
		delete list_bear[i];
		list_bear[i] = NULL;
	}
	list_bear.clear();
	for (int i = 1; i < 8; i++) {
		threatObject* vat_can = new threatObject();
		bool t = vat_can->loadTextureObject("img//threat_left.png", g_renderer);
		if (t == NULL) continue;
		vat_can->set_W_H(WIDTH_THREAT_BEAR / 8, HEIGHT_THREAT_BEAR);
		vat_can->set_X_Y(1500 * i - 840, 100);
		vat_can->set_dan_threat(g_renderer);
		list_bear.push_back(vat_can);
		vat_can = NULL;
	}
}
void Bottom::bottom_start_menu(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, MainO& human, gameMap& tx, Text& time_game, std::vector<threatObject*>& list_bear) {

	background = SDL_CF::loadTexture("img//background.png", g_renderer, 167, 175, 180);
	SDL_RenderCopy(g_renderer, background, NULL, NULL);
	human.resetHuman(g_renderer);
	tx.loadMap("map//map01.dat");
	tx.loadMapTiles(g_renderer);
	tx.set_startMap_XY(0, 0);
	
	time_game.resetTime(SDL_GetTicks() / 1000);
	initBear(list_bear, g_renderer);
}

bool Crash::Crash_Object(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, MainO& human, Map& ga_map, Explosion & exp, std::vector<threatObject*>& list_bear, Audio& audio_game) {
	for (int i = 0; i < list_bear.size(); i++) {
		if (list_bear.size() == 0) return false;
		list_bear.at(i)->set_startMap(ga_map.start_x_, ga_map.start_y_);
		list_bear.at(i)->Renderer_threatO(ga_map, g_renderer);

		//check vat_can crash human
		if (is_crash(list_bear.at(i)->getRectObject(), human.getRectObject()) == true) {
			exp.getRect_x_y_explosion(list_bear.at(i)->getRectObject().x, list_bear.at(i)->getRectObject().y);
			audio_game.playSoundBomb();
			exp.renderExplosion(g_renderer);
			if (human.crash_object_over(g_window, g_renderer, background,audio_game)) return true;
			delete list_bear.at(i);
			list_bear.at(i) = NULL;
			list_bear.erase(list_bear.begin() + i);
			if (human.get_number_die() <= 0) return false;
			if (list_bear.size() == 0) return false;
		}
		//check vat_can_amo to human
		if (is_crash(list_bear.at(i)->dan_T_one()->getRectObject(), human.getRectObject()) == true) {
			exp.getRect_x_y_explosion(human.getRectObject().x, human.getRectObject().y);
			audio_game.playSoundBomb();
			exp.renderExplosion(g_renderer);
			if (human.crash_object_over(g_window, g_renderer, background,audio_game)) return true;
			list_bear.at(i)->dan_T_one()->setRectObject(0, 0, 0, 0);
			if (human.get_number_die() <= 0) return false;

		}
		// check human_amo to vat_can
		for (int j = 0; j < human.GetlistAmop().size(); j++) {
			if (is_crash(list_bear.at(i)->getRectObject(), human.GetlistAmop().at(j)->getRectObject())) {
				exp.getRect_x_y_explosion(list_bear.at(i)->getRectObject().x, list_bear.at(i)->getRectObject().y);
				audio_game.playSoundBomb();
				exp.renderExplosion(g_renderer);
				human.add_score(100);
				human.delete_amo_object(j);
				delete list_bear.at(i);
				list_bear.at(i) = NULL;
				list_bear.erase(list_bear.begin() + i);
				if (list_bear.size() == 0) return false;
				if (human.get_number_die() <= 0) return false;
			}
		}
	}
	return false;
}

bool Crash::is_crash(const SDL_Rect& obj1, const SDL_Rect& obj2) {
	int left_a = obj1.x;
	int right_a = obj1.x + obj1.w;
	int top_a = obj1.y;
	int bottom_a = obj1.y + obj1.h;

	int left_b = obj2.x;
	int right_b = obj2.x + obj2.w;
	int top_b = obj2.y;
	int bottom_b = obj2.y + obj2.h;


	// check object_a crash to_object b
	if (((left_a >= left_b && left_a <= right_b) || (right_a >= left_b && right_a <= right_b)) &&
		((top_a >= top_b && top_a <= bottom_b) || (bottom_a >= top_b && bottom_a <= bottom_b))) return true;

	// check object_b crash to_object a
	if (((left_b >= left_a && left_b <= right_a) || (right_b >= left_a && right_b <= right_a)) &&
		((top_b >= top_a && top_b <= bottom_a) || (bottom_b >= top_a && bottom_b <= bottom_a))) return true;

	return false;
}

