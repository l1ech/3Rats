#pragma once

#include "Panel.h"

class Clock : public Panel
{
private:

	bool day;
	int min;
	int hour;
	int day_counter;

	double spacetime;

	std::string str_time_min;
	std::string str_time_hour;

public:
	Clock();

	void update(double delta);
	void draw(SDL_Renderer* renderTarget);

	void set_time(int hour, int min);
};