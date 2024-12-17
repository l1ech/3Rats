#pragma once

#include <iostream>

#include "../ui/Panel.h"

class Clock : public Panel
{
private:

	bool is_day;

	double spacetime;
	int min;
	int hour;
	int day_counter;

	std::string str_time_min;
	std::string str_time_hour;

public:
	Clock();

	void update(double delta);
	void draw(SDL_Renderer* renderTarget);

	void set_time(int hour, int min);

	int get_day();
	bool day_time();

};