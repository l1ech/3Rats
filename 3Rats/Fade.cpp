#include "Fade.h"

Fade::Fade()
{
}

Fade::~Fade()
{
}

void Fade::update(std::string update_text)
{
	display_text = "Day " + update_text;
	Panel::update();
}

void Fade::draw(SDL_Renderer* renderTarget)
{
	Panel::draw(renderTarget);
}

void Fade::in()
{
	Text::set_coords(0, 0);
	Body::set_cords(0, 0);
}

void Fade::out()
{
	Text::set_coords(999, 999);
	Body::set_cords(999, 999);
}
