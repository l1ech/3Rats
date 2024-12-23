#pragma once

#include "Panel.h"

class Pause : public Panel
{
public:
	void update(std::string update_text);

	void set_surface(SDL_Renderer* render_target);
};