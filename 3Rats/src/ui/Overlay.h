#pragma once

#include "Fade.h"
#include "../core/Clock.h"

class Overlay
{
private:
	Fade* fade;
	Clock* clock;

public:

	void update(double delta);
	void draw(SDL_Renderer* render_target);

	void init(Fade* fade, Clock* clock);
};