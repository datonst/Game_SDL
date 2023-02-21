#pragma once
#ifndef Base_O
#define Base_O
#include "commonFunction.h"

class baseObject {
protected:
	SDL_Rect rectObject;
	SDL_Texture* p_object;
public:
	baseObject();
	~baseObject();
	void setRectObject(const int& x, const int& y, const int& w, const int& h) { rectObject.x = x; rectObject.y = y; rectObject.w = w; rectObject.h = h; };
	SDL_Rect getRectObject() const { return rectObject; };
	void set_x_y_rectObject(const int& x, const int& y) { rectObject.x = x; rectObject.y = y; }
	bool loadTextureObject(const std::string& path, SDL_Renderer* renderer);
	void renderObject(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void set_p_object(SDL_Texture* p_object_) { p_object = p_object_; };
	SDL_Texture* get_p_object() const { return p_object; }
	void freeObject();
};

#endif