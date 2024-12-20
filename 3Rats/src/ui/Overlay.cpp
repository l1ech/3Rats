#include "Overlay.h"

void Overlay::update(double delta)
{
	if (clock->day_time() && flip == true)
	{
		flip = false;
		fade->out();

	}
	else if(!clock->day_time() && flip == false)
	{
		flip = true;
		fade->in();
	} 
}


void Overlay::init(Fade* fade, Clock* clock)
{
	this->fade = fade;
	this->clock = clock;
}
