#include "Overlay.h"

Overlay::Overlay()
{
}

Overlay::~Overlay()
{
}

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

	if (button_music->get_clicked())
	{
		sound->play();
	}
	else
	{
		sound->pause();
	}
}

void Overlay::draw(SDL_Renderer* render_target)
{
}

void Overlay::init(Fade* fade, Sound* sound, Clock* clock, Button* button)
{
	this->fade = fade;
	//this->sound = sound;
	this->clock = clock;
	//this->pause = pause;
	this->button_music = button;
}

void Overlay::pause_music()
{
	sound->pause();
}

void Overlay::play_music()
{
	sound->play();
}
/*
void Overlay::toggle_pause()
{
	pause->toggle();

	if (pause->is_on_screen())
	{
		pause->out();
		//button->
	}
	else
	{
		pause->in();

	}
}

*/

