#pragma once

#include "Sound.h"

class Jukebox 
{
public:
	Jukebox();

	void pause_music();
	void play_music();

	void set_sound(Sound* sound);
	void toggle_music();


private:
	Sound* sound;
};