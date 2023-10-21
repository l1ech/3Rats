#pragma once

#include <SDL_ttf.h>

#include "Body.h"
#include "Text.h"

class Panel : public Body, public Text
{
protected:
	std::string display_text;
	std::string old_display_text;


public:
	Panel();
	~Panel();

	void update();
	void draw(SDL_Renderer* renderTarget);

	void in();
	void out();
};