#pragma once
#ifndef AUDIO_
#define AUDIO_
#include "BaseObject.h"

#include "iostream"

#define WIDTH_AUDIO 333
#define HEIGHT_AUDIO 81
class Audio {
private:
	Mix_Music* music_game;
	Mix_Chunk* bomb;
	Mix_Chunk* collect_money;
	Mix_Chunk* add_heart;
	Mix_Chunk* amo_left;
	Mix_Chunk* amo_right;
	SDL_Rect clip[4];
	baseObject volume_image;
	int index;
	SDL_Rect r_volume;
public:
	Audio();
	~Audio();
	void set_clip_audio();
	bool setAudio(SDL_Renderer* renderer);
	bool setMusic();

	bool setSoundBomb();
	void playSoundBomb();

	bool setSoundCollectMoney();
	void playSoundCollectMoney();

	bool setSoundAddHeart();
	void playSoundAddHeart();

	bool setSoundAmoLeft();
	void playSoundAmoLeft();

	bool setSoundAmoRight();
	void playSoundAmoRight();

	void changeVolume(const int& volume);

	bool setImageVolume(SDL_Renderer* renderer);
	void renderImageVolume(SDL_Renderer* renderer);

	bool setMusicGameOver();
	bool setMusicWinner();
	SDL_Rect getRectImageVolume() const { return r_volume; }

	void runVolume();
};

#endif