#include "Pause.h"

void Pause::update(std::string update_text)
{
	this->display_text = update_text;
	Panel::update();
}

void Pause::set_button(Button* button)
{
	this->button = button;
}

bool Pause::is_on_screen()
{
	return on_screen;
}

void Pause::toggle()
{
	if (on_screen)
	{
		out();
		button->set_coords(999, 999);
	}
	else
	{
		in();
		button->set_coords(0, 90);
	}
}