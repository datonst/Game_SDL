#include "Text.h"

Text::Text()
{
    font = NULL;
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_ = NULL;
    text.x = 0;
    text.y = 0;
    text.h = 0;
    text.w = 0;
    val_time = 0;
    time_val = 0;
    reset_time = 0;
}

Text::~Text()
{
}

bool Text::loadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
    if (text_surface)
    {
        texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
        text.w = text_surface->w;
        text.h = text_surface->h;

        SDL_FreeSurface(text_surface);
    }
    return texture_ != NULL;
}


void Text::setColorText(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void Text::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = { 255, 0, 0 };
        text_color_ = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255 };
        text_color_ = color;

    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = { 0, 0, 0 };
        text_color_ = color;
    }
    else if (type == ORANGE_TEXT)
    {
        SDL_Color color = { 247, 126, 33 };
        text_color_ = color;
    }
    else if (type == BLUE_TEXT)
    {
        SDL_Color color = { 52, 179, 241 };
        text_color_ = color;
    }
}

void Text::rendererText(SDL_Renderer* screen,
    int xp, int yp,
    SDL_Rect* clip /*= NULL*/,
    double angle /*= 0.0*/,
    SDL_Point* center /*= NULL*/,
    SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
{
    SDL_Rect renderQuad = { xp, yp, text.w, text.h };
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}


void Text::setTimeGame() {
    font = TTF_OpenFont("font//dlxfont.ttf", 15);
    if (font == NULL) return;
    setColor(1);
    text.x = SDL_CF::SCREEN_WIDTH - 200;
    text.y = 15;
}

int Text::renderTimeGame(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, Audio& audio_game, const bool &check_win) {
    int rt = 0;
    if(check_win==false) time_val = SDL_GetTicks() / 1000 - reset_time;
    val_time = 200 - time_val;
    if (val_time <= 0) {
        bool ret_game_over = Menu::game_over(g_renderer, audio_game);
        if (ret_game_over == false) return false;
        SDL_RenderPresent(g_renderer);
        int ret_menu = Menu::showMenuStart(g_renderer, background,audio_game);
        if (ret_menu == 1) {
            return true;
        }
        rt = ret_menu;
    }
    std::string str_time = "Time: " + std::to_string(val_time);
    setText(str_time);
    loadFromRenderText(font, g_renderer);
    rendererText(g_renderer, text.x, text.y);
    return rt;
}

void Text::setMoney(int const& money, SDL_Renderer* g_renderer) {
    font = TTF_OpenFont("font//dlxfont.ttf", 15);
    if (font == NULL) return;
    setColor(1);
    image_money.loadTextureObject("img//money.png", g_renderer);
    image_money.setRectObject(2*SDL_CF::SCREEN_WIDTH / 3-50, 8, 30, 30);
    text.x = 2 * SDL_CF::SCREEN_WIDTH / 3;
    text.y = 15;
    std::string str_time = "Money: " + std::to_string(money);
    setText(str_time);
    renderText(g_renderer);
}

void Text::setScore(int const& score,SDL_Renderer* g_renderer) {
    font = TTF_OpenFont("font//dlxfont.ttf", 15);
    if (font == NULL) return;
    std::string str_score = "Score: " + std::to_string(score);
    setText(str_score);
    text.x = SDL_CF::SCREEN_WIDTH / 3;
    text.y = 15;
    setColor(1);
    renderText(g_renderer);
};
void Text::changeMoney(int const& money, SDL_Renderer* g_renderer) {
    std::string str_time = "Money: " + std::to_string(money);
    setText(str_time);
    image_money.renderObject(g_renderer);
    renderText(g_renderer);
}

void Text::changeScore(int const& score, SDL_Renderer* g_renderer) {
    std::string str_score = "Score: " + std::to_string(score);
    setText(str_score);
    renderText(g_renderer);
}


void Text::setMenu(SDL_Renderer* g_renderer) {
    font = TTF_OpenFont("font//menu.ttf", 70);
    if (font == NULL) return;
    renderText(g_renderer);
}


void Text::renderText(SDL_Renderer* g_renderer) {
    loadFromRenderText(font, g_renderer);
    rendererText(g_renderer, text.x, text.y);
    return;
}


void Text::setGameOver(SDL_Renderer* g_renderer) {

    font = TTF_OpenFont("font//game_over.ttf", 100);
    if (font == NULL) return;
    renderText(g_renderer);
}

void Text::setExit(SDL_Renderer* g_renderer) {
    font = TTF_OpenFont("font//menu.ttf", 50);
    if (font == NULL) return;
    setText("Exit");
    text.x = SDL_CF::SCREEN_WIDTH - 100;
    text.y = SDL_CF::SCREEN_HEIGHT - 100;
    setColor(Text::BLACK_TEXT);
    renderText(g_renderer);
}
