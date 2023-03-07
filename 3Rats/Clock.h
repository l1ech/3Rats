#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Body.h"

class Clock : public Body
{
private:
	double count;

	int min;
	int hour;

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


public:
	Clock();
	~Clock();

	void set_renderer(SDL_Renderer* renderTarget);
	void load();

	void update(double delta);
	void draw(SDL_Renderer* renderTarget);

	void set_up(Body* clockframe);

	void set_time( int hour, int min);
};