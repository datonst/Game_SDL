#pragma once
#ifndef TEXT_H
#define TEXT_H
#include "CommonFunction.h"
#include "baseObject.h"
#include "Menu.h"
#include "Audio.h"
class Text
{
public:
    Text();
    ~Text();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        ORANGE_TEXT = 3,
        BLUE_TEXT = 4,
    };

    bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);

    void setColorText(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);

    void rendererText(SDL_Renderer* screen,
        int xp, int yp,
        SDL_Rect* clip = NULL,
        double angle = 0.0,
        SDL_Point* center = NULL,
        SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth() const { return text.w; }
    int getHeight() const { return text.h; }
    SDL_Rect getRectText() const { return text; }

    void setText(const std::string& text) { str_val_ = text; }
    std::string getText() const { return str_val_; }
    void setRectText(int const& x, int const& y) { text.x = x; text.y = y; }
    void setFont(std::string const &s,int const& size){
        font = TTF_OpenFont(s.c_str(), size);
        if (font == NULL) return;
    }


    void setTimeGame();
    int renderTimeGame(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background, Audio& audio_game, const bool& check_win);

    void setMoney(int const& money,SDL_Renderer* g_renderer);
    void setNumberMoney(int const&x) {}
    void changeMoney(int const& money, SDL_Renderer* g_renderer);
    void setScore(int const& score,SDL_Renderer* g_renderer);
    void changeScore(int const& score, SDL_Renderer* g_renderer);
    void setExit(SDL_Renderer* g_renderer);
    void resetTime(int const& x) { reset_time = x; }
    int get_val_time()const { return val_time; }
  
    void setGameOver(SDL_Renderer* g_renderer);
    void setMenu(SDL_Renderer* g_renderer);
    void renderText(SDL_Renderer* g_renderer);

private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    TTF_Font* font;
    baseObject image_money;
    SDL_Rect text;
    unsigned int reset_time;
    int time_val;
    int val_time;
};

#endif