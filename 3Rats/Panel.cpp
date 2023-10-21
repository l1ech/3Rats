#include "Panel.h"

// the code from here is modified frome this stack echange
// https://stackoverflow.com/a/22889483/18288994


Panel::Panel()
{
}

Panel::~Panel()
{
}

void Panel::update()
{
	if (old_display_text == display_text)
	{
		old_display_text = display_text;
		return;
	}
	else
	{
		old_display_text = display_text;
		Text::update(display_text);
	}
}

void Panel::draw(SDL_Renderer* renderTarget)
{
	Body::draw(renderTarget);
	Text::draw(renderTarget);
}

void Panel::in()
{
	Text::set_coords(0, 0);
	Body::set_cords(0, 0);
}

void Panel::out()
{
	Text::set_coords(999, 999);
	Body::set_cords(999, 999);
}
