#include "Curtain.h"

Curtain::Curtain()
{
}

Curtain::~Curtain()
{
}

void Curtain::update(double delta)
{
	pause->update("Pause.");
	clock->update(delta);
	fade->update(std::to_string(clock->get_day()));

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

void Curtain::draw(SDL_Renderer* render_target)
{
	clock->draw(render_target);
	fade->draw(render_target);
	pause->draw(render_target);

}

void Curtain::init(Fade* fade, Sound* sound, Clock* clock, Button* button, Pause* pause)
{
	this->fade = fade;
	//this->sound = sound;
	this->clock = clock;
	this->pause = pause;
	this->button_music = button;
}

void Curtain::pause_music()
{
	sound->pause();
}

void Curtain::play_music()
{
	sound->play();
}
/*
void Curtain::toggle_pause()
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

