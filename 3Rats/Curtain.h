#pragma once

#include "Fade.h"
#include "Clock.h"
#include "Sound.h"
#include "Pause.h"

class Curtain
{
protected:
	Fade* fade;
	Clock* clock;
	//Sound* sound;
	Pause* pause;
	Button* button_music;
public:

	Curtain();
	~Curtain();

	void draw(SDL_Renderer* render_target);

	void init(Fade* fade, Clock* clock, Button* button, Pause* pause);
};