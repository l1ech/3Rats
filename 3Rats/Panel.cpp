#include "Panel.h"

// the code from here is modified frome this stack echange
// https://stackoverflow.com/a/22889483/18288994


Panel::Panel()
{
}

Panel::~Panel()
{
}

void Panel::draw(SDL_Renderer* renderTarget)
{
	Body::draw(renderTarget);
	Text::draw(renderTarget);
}
