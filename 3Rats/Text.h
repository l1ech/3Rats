#pragma once

#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>


class Text {
protected:
	Mix_Music* music;
	SDL_Rect Message_rect;
	SDL_Color red;
	TTF_Font* font;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Renderer* renderer;

	std::string font_path;
	int font_size;
	SDL_Color colour;

	std::string display_text;
	std::string old_display_text;
public:
	Text();
	~Text();

	void update(std::string text);
	void draw(SDL_Renderer* renderTarget);

	void set_renderer(SDL_Renderer* renderTarget);
	void init_text(std::string font_path, int font_size, SDL_Color colour, int x, int y, int w, int h);
	void set_coords(int x, int y);
	void set_music(Mix_Music* music);

};