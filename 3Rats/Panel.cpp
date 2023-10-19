#include "Panel.h"

// the code from here is modified frome this stack echange
// https://stackoverflow.com/a/22889483/18288994


Panel::Panel()
{
	update_text = true;
}

Panel::~Panel()
{
}

void Panel::update(double delta)
{
	
	if (update_text)
	{
		Text::update(display_text);
		update_text = false;
	}
}

void Panel::draw(SDL_Renderer* renderTarget)
{
	Body::draw(renderTarget);
	Text::draw(renderTarget);
}
