#pragma once

#include <SDL_ttf.h>

#include "Body.h"
#include "Text.h"

class Panel : public Body, public Text
{
protected:
	bool update_text;
	std::string display_text;


public:
	Panel();
	~Panel();

	void update(double delta);
	void draw(SDL_Renderer* renderTarget);

};