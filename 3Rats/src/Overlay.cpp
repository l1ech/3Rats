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

void Overlay::init(Fade* fade, Clock* clock)
{
	this->fade = fade;
	this->clock = clock;
}
