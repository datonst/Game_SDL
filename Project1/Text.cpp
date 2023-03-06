#include "Text.h"

Text::Text()
{
    font_time = NULL;
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_ = NULL;
    width_ = 0;
    height_ = 0;

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
        width_ = text_surface->w;
        height_ = text_surface->h;

        SDL_FreeSurface(text_surface);
    }
    return texture_ != NULL;
}

void Text::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
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
    SDL_Rect renderQuad = { xp, yp, width_, height_ };
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}


void Text::setTimeGame() {
    font_time = TTF_OpenFont("font//dlxfont.ttf", 15);
    if (font_time == NULL) return;
    setColor(1);
}

bool Text::renderTimeGame(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background) {
    Uint32 time_val = SDL_GetTicks() / 1000;
    Uint32 val_time = 300 - time_val;
    if (val_time <= 0) {
        SDL_RenderPresent(g_renderer);
        if (MessageBox(NULL, L"Game Over", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
            SDL_CF::quitSDL(g_window, g_renderer);
            SDL_DestroyTexture(background);
            background = NULL;
            return true;
        }
    }
    std::string str_time = "Time: " + std::to_string(val_time);
    setText(str_time);
    loadFromRenderText(font_time, g_renderer);
    rendererText(g_renderer, SDL_CF::SCREEN_WIDTH - 200, 15);
    return false;
}

void Text::setMoney() {
    font_time = TTF_OpenFont("font//dlxfont.ttf", 15);
    if (font_time == NULL) return;
    setColor(1);
}

void Text::renderMoney(int const& money,SDL_Renderer* g_renderer) {
    std::string str_time = "Money: " + std::to_string(money);
    setText(str_time);
    loadFromRenderText(font_time, g_renderer);
    rendererText(g_renderer, SDL_CF::SCREEN_WIDTH/2, 15);
    return;
}