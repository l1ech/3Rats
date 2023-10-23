#pragma once

#include <SDL_mixer.h>


class Sound
{
private:
	Mix_Music* music;
	bool music_playing;

public:
	Sound();

	void init();
	void pause();
	void play();

	bool is_music_playing();
};