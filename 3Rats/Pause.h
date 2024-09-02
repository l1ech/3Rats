#pragma once

#include "Panel.h"
#include "Button.h"

class Pause : public Panel
{
private:
	Button* button_music;

public:
	void update(std::string update_text);

	void set_button(Button* button_music);
	bool is_on_screen();
	void toggle();

	void out();
	void in();

};