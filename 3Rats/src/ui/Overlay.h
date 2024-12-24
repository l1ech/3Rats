#pragma once

#include "Fade.h"
#include "../stage/Clock.h"

class Overlay
{
private:
	Fade* fade;
	Clock* clock;

	bool flip = false;

public:

	void update(double delta);
	void draw(SDL_Renderer* render_target);

	void init(Fade* fade, Clock* clock);
};