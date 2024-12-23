#include "Pause.h"

void Pause::update(std::string update_text)
{
	this->display_text = update_text;
}

void Pause::set_surface(SDL_Renderer *render_target)
{
	Body::set_surface(render_target);
	Text::set_renderer(render_target);
}
