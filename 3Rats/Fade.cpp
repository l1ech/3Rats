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