﻿#include "BaseObject.h"
#include <iostream>
baseObject::baseObject(){
	rectObject.x=0;
	rectObject.y=0;
	rectObject.w=0;
	rectObject.h=0;
	p_object=NULL;
}

baseObject::~baseObject(){
	freeObject();
}


bool baseObject::loadTextureObject(const std::string& path, SDL_Renderer* renderer) {
	p_object = SDL_CF::loadTexture(path, renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
	return p_object != NULL;
}

void baseObject::renderObject(SDL_Renderer *des,const SDL_Rect* clip /* =NULL*/){
	SDL_RenderCopy(des,p_object,clip,&rectObject);
}

void baseObject::freeObject(){
	if(p_object!=NULL) {
		SDL_DestroyTexture(p_object);
		rectObject.w=0;
		rectObject.h=0;
	}
}