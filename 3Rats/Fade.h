#pragma once

#include "Panel.h"

class Fade : public Panel
{
public:
	Fade();
	~Fade();

	void update(std::string update_text);
	void draw(SDL_Renderer* renderTarget);

};