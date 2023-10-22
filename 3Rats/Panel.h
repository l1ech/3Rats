#pragma once

#include <SDL_ttf.h>

#include "Body.h"
#include "Text.h"

class Panel : public Body, public Text
{
protected:
	bool on_screen;


public:
	Panel();
	~Panel();

	void update();
	void draw(SDL_Renderer* renderTarget);

	void in();
	void out();
};