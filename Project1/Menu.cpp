#include "Menu.h"


bool Menu::showMenu(SDL_Renderer* renderer, SDL_Texture* g_menu)
{
	g_menu = SDL_CF::loadTexture("img//start_img.png",renderer,255,255,255);
	if (g_menu == NULL)
	{
		return true;
	}

	const int kMenuItemNum = 2;
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 200;
	pos_arr[0].y = 400;

	pos_arr[1].x = 200;
	pos_arr[1].y = 450;

	Text text_menu[kMenuItemNum];

	text_menu[0].setText("Start");
	text_menu[0].setColor(Text::BLACK_TEXT);
	text_menu[0].setRectText(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].setText("Exit");
	text_menu[1].setColor(Text::BLACK_TEXT);
	text_menu[1].setRectText(pos_arr[1].x, pos_arr[1].y);
	for (int i = 0; i < kMenuItemNum; ++i)
	{
		text_menu[i].setMenu(renderer);
	}
	bool selected[kMenuItemNum] = { 0, 0 };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while (true)
	{
		SDL_RenderCopy(renderer, g_menu, NULL, NULL);
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
				return true;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;
				for (int i = 0; i < kMenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].getRectText()))
					{
						if (selected[i] == false)
						{
							selected[i] = true;
							text_menu[i].setColor(Text::RED_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = false;
							text_menu[i].setColor(Text::BLACK_TEXT);
						}
					}
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;
				for (int i = 0; i < kMenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].getRectText()))
					{
						return i;
					}
				}
			}
			break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return true;
				}
			default:
				break;
			}
		}
		for (int i = 0; i < kMenuItemNum; ++i)
		{
			text_menu[i].renderText(renderer);
		}
		SDL_RenderPresent(renderer);
	}
	return true;
}

bool Menu::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

bool Menu::game_over(SDL_Renderer* renderer) {
	const int kMenuItemNum = 2;
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = SDL_CF::SCREEN_WIDTH / 5;
	pos_arr[0].y = SDL_CF::SCREEN_HEIGHT / 3;

	pos_arr[1].x = SDL_CF::SCREEN_WIDTH-100;
	pos_arr[1].y = SDL_CF::SCREEN_HEIGHT-100;

	Text text_menu[kMenuItemNum];

	text_menu[0].setText("GAME OVER!");
	text_menu[0].setColor(Text::RED_TEXT);
	text_menu[0].setRectText(pos_arr[0].x, pos_arr[0].y);
	text_menu[0].setGameOver(renderer);


	text_menu[1].setText("Exit");
	text_menu[1].setColor(Text::BLACK_TEXT);
	text_menu[1].setRectText(pos_arr[1].x, pos_arr[1].y);
	text_menu[1].setMenu(renderer);
	bool selected[kMenuItemNum] = { 0, 0 };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while (true)
	{
		srand(unsigned int(time(0)));
		text_menu[0].setColorText(rand()%256, rand() % 256, rand() % 256);
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
				return true;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;
				if (CheckFocusWithRect(xm, ym, text_menu[1].getRectText()))
				{
					if (selected[1] == false)
					{
						selected[1] = true;
						text_menu[1].setColor(Text::RED_TEXT);
					}
				}
				else
				{
					if (selected[1] == true)
					{
						selected[1] = false;
						text_menu[1].setColor(Text::BLACK_TEXT);
					}
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;
				if (CheckFocusWithRect(xm, ym, text_menu[1].getRectText()))
				{
					return true;
				}
			}
			break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return true;
				}
			default:
				break;
			}
		}
		for (int i = 0; i < kMenuItemNum; ++i)
		{
			text_menu[i].renderText(renderer);
		}
		SDL_RenderPresent(renderer);
	}
	return true;
}


void Menu::initBear(std::vector<threatObject*> &list_bear, SDL_Renderer* g_renderer) {
	for (int i = 0; i < list_bear.size(); i++) {
		delete list_bear[i];
		list_bear[i] = NULL;
	}
	list_bear.clear();
	for (int i = 1; i < 8; i++) {
		threatObject* vat_can = new threatObject();
		bool t = vat_can->loadTextureObject("img//threat_left.png", g_renderer);
		if (t == NULL) continue;
		vat_can->set_W_H(WIDTH_THREAT_BEAR / 8, HEIGTH_THREAT_BEAR);
		vat_can->set_X_Y(1500 * i - 840, 100);
		vat_can->set_dan_threat(g_renderer);
		list_bear.push_back(vat_can);
		vat_can = NULL;
	}
}

