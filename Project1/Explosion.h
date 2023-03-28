#pragma once
#ifndef EXPL_H
#define EXPL_H

#include"BaseObject.h"
class Explosion : public baseObject {
public:
	Explosion();
	~Explosion();

	void set_clip();
	void getRect_x_y_explosion(int const& x, int const& y) { rectObject.x = x-25, rectObject.y = y-45; }
	void renderExplosion(SDL_Renderer* screen);
private:
	const int frame_width_=1200;
	const int frame_height_=165;
	SDL_Rect clip[8];

};

#endif
