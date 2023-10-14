#pragma once

#include "Panel.h"

class Clock : public Panel
{
private:
	bool day;

	double count;

	int min;
	int hour;

	int day_counter;

	bool is_running;

	std::string str_time_min;
	std::string str_time_hour;

	std::string time;

	bool update_time;

public:

	Clock();

	void set_time(int hour, int min);

	void update(double delta);

	bool get_running()
	{
		return is_running;
	}

};