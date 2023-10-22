#pragma once

#include "Panel.h"
#include "Button.h"

class Pause : public Panel
{
private:
	Button* button;
public:
	void update(std::string update_text);

	void set_button(Button* button);
	bool is_on_screen();
	void toggle();

};