#include"Audio.h"

Audio::Audio() {
	r_volume.x = SDL_CF::SCREEN_WIDTH-100;
	r_volume.y = 20;
	r_volume.w = WIDTH_AUDIO / 4;
	r_volume.h = HEIGHT_AUDIO;
	set_clip_audio();
	music_game = NULL;
	bomb = NULL;
	amo_left = NULL;
	amo_right = NULL;
	index = 0;
}
Audio::~Audio() {
	Mix_FreeChunk(bomb);
	Mix_FreeMusic(music_game);
	Mix_FreeChunk(amo_left);
	Mix_FreeChunk(amo_right);
}

void Audio::set_clip_audio() {
	for (int i = 0; i < 4; i++) {
		clip[i].x = i * WIDTH_AUDIO / 4;
		clip[i].y = 0;
		clip[i].w = WIDTH_AUDIO / 4;
		clip[i].h = HEIGHT_AUDIO;
	}
}
bool Audio::setAudio(SDL_Renderer* renderer) {
	if (setMusic() == false) return false;
	if(setSoundAmoLeft()==false) return false;
	if(setSoundAmoRight()==false) return false;
	if (setSoundBomb() == false) return false;
	if (setSoundCollectMoney() == false) return false;
	if (setSoundAddHeart() == false) return false;
	if (setImageVolume(renderer) == false) return false;
	return true;
}
bool Audio::setMusic() {
	Mix_HaltMusic();
	music_game = Mix_LoadMUS("music//chill.mp3");
	if (music_game == NULL) {
		std::cerr << "Error set Music file chill.mp3 " << Mix_GetError << std::endl;
		return false;
	}
	int is_music = Mix_PlayMusic(music_game, -1);
	if (is_music == -1) {
		return false;
	}
	Mix_PausedMusic();
	return true;
};


bool Audio::setSoundBomb() {
	bomb = Mix_LoadWAV("sound//explosion.wav");
	if (bomb == NULL) {
		std::cerr << "Error set Bomb file " << Mix_GetError << std::endl;
		return false;
	}
	return true;
};
void  Audio::playSoundBomb() {
	Mix_PlayChannel(-1, bomb, 0);
};

bool Audio::setSoundCollectMoney() {
	collect_money = Mix_LoadWAV("sound//collectcoin.wav");
	if (collect_money == NULL) {
		std::cerr << "Error set collectcoin file " << Mix_GetError << std::endl;
		return false;
	}
	return true;
}

void Audio::playSoundCollectMoney() {
	Mix_PlayChannel(-1, collect_money, 0);
}

bool Audio::setSoundAddHeart() {
	add_heart = Mix_LoadWAV("sound//addheart.wav");
	if (add_heart == NULL) {
		std::cerr << "Error set addheart file " << Mix_GetError << std::endl;
		return false;
	}
	return true;
}
void Audio::playSoundAddHeart() {
	Mix_PlayChannel(-1, add_heart, 0);
}

bool Audio::setSoundAmoLeft() {
	amo_left = Mix_LoadWAV("sound//gun_left.wav");
	if (amo_left == NULL) {
		std::cerr << "Error set Amo Left file " << Mix_GetError << std::endl;
		return false;
	}
	return true;
};

void  Audio::playSoundAmoLeft() {
	 Mix_PlayChannel(-1, amo_left, 0);
};

bool Audio::setSoundAmoRight() {
	amo_right = Mix_LoadWAV("sound//gun_right.wav");
	if (amo_right == NULL) {
		std::cerr << "Error set Load Amo Right file " << Mix_GetError << std::endl;
		return false;
	}
	return true;
};

void  Audio::playSoundAmoRight() {
	 Mix_PlayChannel(-1, amo_right, 0);
};

void Audio::changeVolume(const int& volume) {
	if (volume == 3) {
		Mix_PauseMusic();
		Mix_VolumeMusic(0);
		Mix_VolumeChunk(bomb, 0);
		Mix_VolumeChunk(amo_left, 0);
		Mix_VolumeChunk(amo_right, 0);
		Mix_VolumeChunk(collect_money, 0);
		Mix_VolumeChunk(add_heart, 0);
	}
	else if (volume == 2) {
		Mix_ResumeMusic();
		Mix_VolumeMusic(MIX_MAX_VOLUME/4);
		Mix_VolumeChunk(bomb, MIX_MAX_VOLUME / 4);
		Mix_VolumeChunk(amo_left, MIX_MAX_VOLUME / 4);
		Mix_VolumeChunk(amo_right, MIX_MAX_VOLUME / 4);
		Mix_VolumeChunk(collect_money, MIX_MAX_VOLUME / 4);
		Mix_VolumeChunk(add_heart, MIX_MAX_VOLUME / 4);
	}
	else if (volume == 1) {
		Mix_ResumeMusic();
		Mix_VolumeMusic(3* MIX_MAX_VOLUME /5 );
		Mix_VolumeChunk(bomb, 3 * MIX_MAX_VOLUME / 5);
		Mix_VolumeChunk(amo_left, 3 * MIX_MAX_VOLUME / 5);
		Mix_VolumeChunk(amo_right, 3 * MIX_MAX_VOLUME / 5);
		Mix_VolumeChunk(collect_money, 3 * MIX_MAX_VOLUME / 5);
		Mix_VolumeChunk(add_heart, 3 * MIX_MAX_VOLUME / 5);
	}
	else if (volume == 0) {
		Mix_ResumeMusic();
		Mix_VolumeMusic(MIX_MAX_VOLUME-2);
		Mix_VolumeChunk(bomb, MIX_MAX_VOLUME - 2);
		Mix_VolumeChunk(amo_left, MIX_MAX_VOLUME - 2);
		Mix_VolumeChunk(amo_right, MIX_MAX_VOLUME - 2);
		Mix_VolumeChunk(collect_money, MIX_MAX_VOLUME - 2);
		Mix_VolumeChunk(add_heart, MIX_MAX_VOLUME - 2);
		
	}
}


bool Audio::setImageVolume(SDL_Renderer* renderer) {
	bool load_image=volume_image.loadTextureObject("img//Volume.png", renderer);
	if (load_image == false) return false;
	volume_image.setRectObject(r_volume.x, r_volume.y, r_volume.w, r_volume.h);
	return true;
};

void Audio::renderImageVolume(SDL_Renderer* renderer) {
	
	volume_image.renderObject(renderer, &clip[index]);
}

void Audio::runVolume() {
	index++;
	if (index >= 4) index = 0;
	changeVolume(index);
}

bool Audio::setMusicGameOver() {
	Mix_HaltMusic();
	music_game = Mix_LoadMUS("music//gameover.mp3");
	if (music_game == NULL) {
		std::cerr << "Error set Music file gameover.mp3 " << Mix_GetError << std::endl;
		return false;
	}
	int is_music = Mix_PlayMusic(music_game, -1);
	if (is_music == -1) {
		return false;
	}
	return true;
}

bool Audio::setMusicWinner(){
	
	music_game = Mix_LoadMUS("music//win.mp3");
	if (music_game == NULL) {
		std::cerr << "Error set Music file win.mp3 " << Mix_GetError << std::endl;
		return false;
	}
	int is_music = Mix_PlayMusic(music_game, -1);
	if (is_music == -1) {
		return false;
	}
	return true;
	
}