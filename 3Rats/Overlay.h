#pragma once

#include "Fade.h"
#include "Clock.h"
#include "Sound.h"
#include "Pause.h"
#include "Button.h"

class Overlay
{
private:
	Fade* fade;
	Clock* clock;
	Sound* sound;
	Pause* pause;
	Button* button_music;
public:

	Overlay();
	~Overlay();

	void update(double delta);
	void draw(SDL_Renderer* render_target);

	void init(Fade* fade, Sound* sound, Clock* clock, Button* button);

	void pause_music();
	void play_music();
};