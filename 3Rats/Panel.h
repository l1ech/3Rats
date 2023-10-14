#pragma once

#include <SDL_ttf.h>

#include "Body.h"
#include "Text.h"

class Panel : public Body, public Text
{
private:

public:
	Panel();
	~Panel();
	void draw(SDL_Renderer* renderTarget);
};