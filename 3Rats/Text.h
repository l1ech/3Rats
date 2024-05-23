#pragma once

#include <SDL_ttf.h>
#include <iostream>

class Text 
{
protected:

	std::string font_path;
	SDL_Renderer* render_target;
	SDL_Texture* Message;

	SDL_Rect message_rect;

	SDL_Color colour;
	TTF_Font* font;
	SDL_Surface* surface_message;

	int font_size;

	std::string display_text;
	std::string old_display_text;


public:

	Text();
	~Text();

	void update(std::string text);
	void draw(SDL_Renderer* renderTarget);

	void set_renderer(SDL_Renderer* renderTarget);
	void init(std::string font_path, int font_size, SDL_Color colour, int x, int y, int w, int h);
	void set_coords(int x, int y);
	void set_width(int w);

};