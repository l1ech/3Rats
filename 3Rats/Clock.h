#pragma once

#include <SDL_ttf.h>

#include "Body.h"
//#include "Text.h"

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

	SDL_Renderer* renderer;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Texture* texture;

	SDL_Rect cropRect;
	SDL_Rect Message_rect;
	SDL_Color red;
	TTF_Font* font;

	Body* clockframe;

	bool update_time;

	//Text* text;

public:
	Clock();
	~Clock();

	void set_renderer(SDL_Renderer* renderTarget);
	void load();

	void update(double delta);
	void draw(SDL_Renderer* renderTarget);

	void set_up(Body* clockframe);

	void set_time( int hour, int min);

	bool get_running()
	{
		return is_running;
	}
};