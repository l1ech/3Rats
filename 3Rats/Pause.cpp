#include "Pause.h"

void Pause::update(std::string update_text)
{
	this->display_text = update_text;
	Panel::update();
}

void Pause::set_button(Button* button_music)
{
	this->button_music = button_music;
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
		button_music->set_coords(999, 999);
	}
	else
	{
		in();
		button_music->set_coords(0, 90);
	}
}