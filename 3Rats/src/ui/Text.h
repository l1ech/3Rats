#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <iostream>

#include "../core/Constants.h"

//#include "../core/Texture_Manager.h"

class Text {
private:
	SDL_Rect Message_rect;
	SDL_Color red;
	TTF_Font* font;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Renderer* renderer;

	std::string font_path;
	int font_size;
	SDL_Color colour;

	std::string message_string;

	std::string text_name;


public:
	Text();
	~Text();

	void update(std::string time);
	void draw(SDL_Renderer* renderTarget);

	void set_renderer(SDL_Renderer* renderTarget);
	void init_text(std::string font_path, int font_size, SDL_Color colour, int x, int y, int w, int h);
	void set_coords(int x, int y);

	void set_text_name(std::string name);
};