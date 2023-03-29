#include "Menu.h"


int Menu::showMenu(SDL_Renderer* renderer, SDL_Texture* g_menu, Audio& audio_game)
{
	baseObject start_menu;
	start_menu.setColorKey(0, 0, 0);
	start_menu.loadTextureObject("img//home.png", renderer);
	start_menu.setRectObject(20, 20, 81, 82);
	g_menu = SDL_CF::loadTexture("img//continue_menu.jpg",renderer,255,255,255);
	if (g_menu == NULL)
	{
		return true;
	}

	const int kMenuItemNum = 2;
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 500;
	pos_arr[0].y = 250;

	pos_arr[1].x = 550;
	pos_arr[1].y = 350;

	Text text_menu[kMenuItemNum];

	text_menu[0].setText("Continue");
	text_menu[0].setColor(Text::WHITE_TEXT);
	text_menu[0].setRectText(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].setText("Exit");
	text_menu[1].setColor(Text::WHITE_TEXT);
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
							text_menu[i].setColor(Text::BLUE_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = false;
							text_menu[i].setColor(Text::WHITE_TEXT);
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
				if (CheckFocusWithRect(xm, ym, audio_game.getRectImageVolume())) {
					audio_game.runVolume();
				}
				if (CheckFocusWithRect(xm, ym, start_menu.getRectObject())) {
					return showMenuStart(renderer,g_menu,audio_game);
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
		start_menu.renderObject(renderer);
		audio_game.renderImageVolume(renderer);
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

bool Menu::game_over(SDL_Renderer* renderer, Audio& audio_game) {
	if(audio_game.setMusicGameOver()==false) return true;
	const int kMenuItemNum = 2;
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = SDL_CF::SCREEN_WIDTH / 5;
	pos_arr[0].y = SDL_CF::SCREEN_HEIGHT / 3;

	pos_arr[1].x = SDL_CF::SCREEN_WIDTH-150;
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


int Menu::showMenuStart(SDL_Renderer* renderer, SDL_Texture* g_menu, Audio& audio_game) {
	audio_game.setMusic();
	int check = 2;
	g_menu = SDL_CF::loadTexture("img//start_img.jpg", renderer, 0, 0, 0);
	if (g_menu == NULL)
	{
		return true;
	}
	baseObject dinosaur;
	baseObject wolf;
	baseObject tick;
	tick.setColorKey(0, 0,0);
	tick.loadTextureObject("img//tick.png", renderer);
	tick.setRectObject(200, 310, 40, 40);
	dinosaur.loadTextureObject("img//player_pw.png", renderer);
	dinosaur.setRectObject(100, 300, 60, 57);
	wolf.loadTextureObject("img//wolf_pw.png", renderer);
	wolf.setRectObject(100, 400, 79, 40);
	const int kMenuItemNum = 2;
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = SDL_CF::SCREEN_WIDTH*3/4;
	pos_arr[0].y = SDL_CF::SCREEN_HEIGHT *3/5-100;

	pos_arr[1].x = SDL_CF::SCREEN_WIDTH * 3 / 4;
	pos_arr[1].y = SDL_CF::SCREEN_HEIGHT * 5 / 7-100;

	Text text_menu[kMenuItemNum];
	Text Player;

	Player.setText("Player");
	Player.setColor(Text::ORANGE_TEXT);
	Player.setRectText(100, 200);
	Player.setMenu(renderer);
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
						if (i == 0) return check;
						return i;
					}
				}
				if (CheckFocusWithRect(xm, ym,dinosaur.getRectObject()))
				{
					tick.set_x_y_rectObject(200, 310);
					check = 2;
				}
				if (CheckFocusWithRect(xm, ym, wolf.getRectObject()))
				{
					tick.set_x_y_rectObject(200, 400);
					check = 3;
				}
				if (CheckFocusWithRect(xm, ym, audio_game.getRectImageVolume())) {
					audio_game.runVolume();
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
		dinosaur.renderObject(renderer);
		wolf.renderObject(renderer);
		tick.renderObject(renderer);
		Player.renderText(renderer);
		audio_game.renderImageVolume(renderer);
		SDL_RenderPresent(renderer);
	}
	return true;
};

