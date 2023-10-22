#include "Overlay.h"

void Overlay::update(double delta)
{
	if (!clock->day_time())
	{
		fade->in();
	}
	else if (clock->day_time())
	{
		fade->out();
	}
}

void Overlay::draw(SDL_Renderer* render_target)
{
}

void Overlay::init(Fade* fade, Sound* sound, Clock* clock)
{
	this->fade = fade;
	this->sound = sound;
	this->clock = clock;
	//this->pause = pause;
	//this->button = button;
}

void Overlay::pause_music()
{
	sound->pause();
}

void Overlay::play_music()
{
	sound->play();
}

void Overlay::toggle_pause()
{
	pause->toggle();

	if (pause->is_on_screen())
	{
		pause->out();
		button
	}
}

