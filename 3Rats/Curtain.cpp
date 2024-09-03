#include "Curtain.h"

Curtain::Curtain()
{
}

Curtain::~Curtain()
{
}

void Curtain::init(Fade* fade, Clock* clock, Button* button, Pause* pause)
{
	this->fade = fade;
	this->clock = clock;
	this->pause = pause;
	this->button_music = button;
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

