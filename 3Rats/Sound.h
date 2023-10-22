#pragma once

#include <SDL_mixer.h>


class Sound
{
private:
	Mix_Music* music;
public:
	void init();
	void pause();
	void play();
};