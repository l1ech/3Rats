#include "Pause.h"

void Pause::update(std::string update_text)
{
	set_display_text(update_text);
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
		Pause::out();
		Panel::out();
	}
	else
	{
		Pause::in();
		Panel::in();
	}
}

void Pause::out()
{
	button_music->set_cords(999, 999);
}

void Pause::in()
{
	button_music->set_cords(200, 100);
}
