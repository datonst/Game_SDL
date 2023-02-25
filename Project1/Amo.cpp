#include "Amo.h"

Amop::Amop() {
	SPEED_GUN = 0;
	x_vall = SPEED_GUN;
	y_vall = SPEED_GUN;
	is_move = false;
	amo_type = 0;
	rectObject.x = 0;
	rectObject.y = 0;
	rectObject.w = 0;
	rectObject.h = 0;
};

Amop::~Amop() {
	;
};


void Amop::Handle_MM(int const& x_border, int const& y_border) {
	rectObject.x += SPEED_GUN;
	if (rectObject.x<0 || rectObject.x>x_border) is_move = false;
	if (rectObject.y<0 || rectObject.y>y_border) is_move = false;
};

