#pragma once
#ifndef TEXT_H
#define TEXT_H
#include "CommonFunction.h"

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
    void Free();

    void setColorText(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);

    void rendererText(SDL_Renderer* screen,
        int xp, int yp,
        SDL_Rect* clip = NULL,
        double angle = 0.0,
        SDL_Point* center = NULL,
        SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    void setText(const std::string& text) { str_val_ = text; }
    std::string getText() const { return str_val_; }

    void setTimeGame();
    bool renderTimeGame(SDL_Window* g_window, SDL_Renderer* g_renderer, SDL_Texture* background);

    void setMoney();
    void renderMoney(int const& money,SDL_Renderer* g_renderer);

private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
    TTF_Font* font_time;
};

#endif