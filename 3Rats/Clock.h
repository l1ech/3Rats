#pragma once

#include <SDL_ttf.h>

#include "Body.h"
#include "Text.h"

class Clock : public Body
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

	Body* clockframe;

	bool update_time;

	Text* text;

public:
	Clock();
	~Clock();

	void update(double delta);
	void draw(SDL_Renderer* renderTarget);

	void set_body(Body* clock_frame);
	void set_text(Text* text_time);

	void set_time( int hour, int min);

	bool get_running()
	{
		return is_running;
	}
};