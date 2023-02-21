#include "Amo.h"

Amop::Amop() {
	x_vall = 5;
	y_vall = 5;
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
	rectObject.x += 5;
	if (rectObject.x<0 || rectObject.x>x_border) is_move = false;
	if (rectObject.y<0 || rectObject.y>y_border) is_move = false;
};

