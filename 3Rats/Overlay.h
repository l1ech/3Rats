#pragma once

#include "Fade.h"
#include "Clock.h"
#include "Pause.h"
#include "Sound.h"
#include "Button.h"

class Overlay
{
private:
	Fade* fade;
	Clock* clock;
	Sound* sound;
	Pause* pause;
	Button* button;
public:

	void update(double delta);
	void draw(SDL_Renderer* render_target);

	void init(Fade* fade, Sound* sound, Clock* clock);

	void pause_music();
	void play_music();

	void toggle_pause();


};