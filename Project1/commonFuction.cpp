#include "CommonFunction.h"
#include <iostream>



void SDL_CF::initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		SDL_CF::logSDLError(std::cout, "SDL_Init", true);

	window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, 
	// SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == nullptr) SDL_CF::logSDLError(std::cout, "CreateWindow", true);


	//Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);

	//Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
	//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

	if (renderer == nullptr) SDL_CF::logSDLError(std::cout, "CreateRenderer", true);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	//	SDL_SetRenderDrawColor(g_bkground,255,255,255,255);
	//	int imgflag=IMG_INIT_PNG;
	//	if(!IMG_Init(imgflag) && imgflag){
	//		logSDLError(std::cout, "imgflag", true);
	//	}
}


void SDL_CF::waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}


void SDL_CF::logSDLError(std::ostream& os,
	const std::string& msg, bool fatal)
{
	os << msg << " Error: " << SDL_GetError() << std::endl;
	if (fatal) {
		SDL_Quit();
		exit(1);
	}
}

void SDL_CF::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Texture* SDL_CF::loadTexture(const std::string& path, SDL_Renderer* renderer, const int& COLOR_KEY_R, const int& COLOR_KEY_G, const int& COLOR_KEY_B) {
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path << "SDL_image Error: " << IMG_GetError();
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr) std::cout << "Unable to creat texture from " << path << "SDL Error: " << IMG_GetError();
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

bool SDL_CF::is_crash(const SDL_Rect &obj1, const SDL_Rect &obj2){
	int left_a=obj1.x;
	int right_a=obj1.x+obj1.w;
	int top_a=obj1.y;
	int bottom_a=obj1.y+obj1.h;

	int left_b=obj2.x;
	int right_b=obj2.x+obj2.w;
	int top_b=obj2.y;
	int bottom_b=obj2.y+obj2.h;


/*	//check object b crash to object a
	if( (left_b>left_a && left_b<right_a && top_b<bottom_a && top_b>top_a)  //  check corner II of object b   ( object a    <--  object b) 
		|| (right_b>left_a && right_b<right_a && top_b<bottom_a && top_b >top_a) // check corner  I of object b ( object b --> object a) 
		|| (left_b>left_a && left_b<right_a && bottom_b<bottom_a && bottom_b >top_a) // check corner III of object b   ( object a    <--  object b) 
		|| (right_b>left_a && right_b<right_a && bottom_b<bottom_a && bottom_b >top_a))  // check corner IV of object b ( object b --> object a)
	{
		return true;
	}

	//check object a crash to object b
	if( (left_a>left_b && left_a<right_b && top_a<bottom_b && top_a>top_b)        //corner II of object a(object b < --object a)
		|| (right_a>left_b && right_a<right_b && top_a<bottom_b && top_a >top_b) // corner  I of object a ( object a --> object b) 
		|| (left_a>left_b && left_a<right_b && bottom_a<bottom_b && bottom_a >top_b) //corner III of object a(object b < --object a)
		|| (right_a>left_b && right_a<right_b && bottom_a<bottom_b && bottom_a >top_b)) // check corner IV of object a ( object a --> object b)
	{
		return true;
	}
	*/


	// check object_a crash to_object b
	if ( ((left_a >= left_b && left_a <=right_b) || (right_a>= left_b && right_a<=right_b) ) &&
		( (top_a >= top_b && top_a <=  bottom_b) || (bottom_a >= top_b &&bottom_a <= bottom_b)) ) return true;

	// check object_b crash to_object a
	if (((left_b >= left_a && left_b <= right_a) || (right_b >= left_a && right_b <= right_a)) &&
		((top_b >= top_a && top_b <= bottom_a) || (bottom_b >= top_a && bottom_b <= bottom_a))) return true;

	return false;
}
