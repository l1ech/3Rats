#include "Clock.h"

Clock::Clock()
{
	day_counter = 0;
	day = true;
}

void Clock::update(double delta)
{
	spacetime += delta;

	//std::cout << count << std::endl;

	if (spacetime >= 5)
	{
		spacetime = 0;
		min++;
		update_text = true;
	}

	if (min >= 60)
	{
		min = 0;
		hour++;
		update_text = true;
	}

	if (hour >= 24)
	{
		hour = 0;
		update_text = true;
	}

	str_time_min = std::to_string((int)min);
	str_time_hour = std::to_string((int)hour);

	if (str_time_min.size() == 1)
	{
		str_time_min = "0" + str_time_min;
	}

	if (str_time_hour.size() == 1)
	{
		str_time_hour = "0" + str_time_hour;
	}

	display_text = str_time_hour + ":" + str_time_min;

	// befor i made it with this update flag memory was to big to fast. 
	// alternative idea: somehow free space like in the ~panel.

	Panel::update(delta);

	if (hour == 16 && min == 35 && day && !1)
	{
		day_counter++;
		std::cout << "day# " << day_counter << " passed. its time to sleep now!" << std::endl;
		// is player back at base?
		day = false;
	}
}

void Clock::draw(SDL_Renderer* renderTarget)
{
	Panel::draw(renderTarget);
}

void Clock::set_time(int hour, int min)
{
	spacetime = 0;
	this->min = min;
	this->hour = hour;
}
