#include "Explosion.h"

Explosion::Explosion()
{
    set_clip();
}

Explosion::~Explosion()
{

}



void  Explosion::set_clip() {
    setRectObject(0, 0, frame_width_/8, frame_height_);
    for (int i = 0; i < 8; i++) {
        clip[i].x = i * frame_width_ / 8;
        clip[i].y = 0;
        clip[i].w = frame_width_/8;
        clip[i].h = frame_height_;
    }
}

void Explosion::renderExplosion(SDL_Renderer* screen)
{
    for (int i = 0; i < 8; i++) {
        renderObject(screen, &clip[i]);
        SDL_RenderPresent(screen);

    }

}