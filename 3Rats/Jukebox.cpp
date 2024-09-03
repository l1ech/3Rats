#include "Jukebox.h"

Jukebox::Jukebox()
{
}

void Jukebox::pause_music()
{
	sound->pause();
}

void Jukebox::play_music()
{
	sound->play();
}

void Jukebox::set_sound(Sound* sound_p)
{
	sound = sound_p;
}

void Jukebox::toggle_music()
{
	if (sound->is_music_playing())
	{
		sound->pause();
	}
	else
	{
		sound->play();
	}
}
