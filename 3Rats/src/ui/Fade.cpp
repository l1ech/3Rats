#include "Fade.h"

Fade::Fade()
{
}

Fade::~Fade()
{
}

void Fade::update(std::string update_text)
{
	display_text = "[Fade]: Day " + update_text;
    //SDL_Log("[Fade]: Update called with text: %s", update_text.c_str());
	Panel::update();
}

void Fade::draw(SDL_Renderer* renderTarget)
{
	bool isFading = false;
	int alpha = 255;

    //SDL_Log("[Fade]: Draw called");

    if (isFading)
    {
        SDL_SetRenderDrawBlendMode(renderTarget, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, alpha);
        SDL_RenderFillRect(renderTarget, NULL);
        SDL_SetRenderDrawBlendMode(renderTarget, SDL_BLENDMODE_NONE);
    }
}

void Fade::set_surface(SDL_Renderer *render_target)
{
    Body::set_surface(render_target);
    Text::set_renderer(render_target);
}
