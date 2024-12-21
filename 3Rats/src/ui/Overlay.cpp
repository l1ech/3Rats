#include "Overlay.h"

void Overlay::update(double delta)
{
    std::cout << "[Overlay]: update called with delta: " << delta << std::endl;

    if (clock->day_time() && flip == true)
    {
        std::cout << "[Overlay]: Day time detected, calling fade->out()" << std::endl;
        flip = false;
        fade->out();
    }
    else if (!clock->day_time() && flip == false)
    {
        std::cout << "[Overlay]: Night time detected, calling fade->in()" << std::endl;
        flip = true;
        fade->in();
    }
}

void Overlay::init(Fade* fade, Clock* clock)
{
	this->fade = fade;
	this->clock = clock;
}
