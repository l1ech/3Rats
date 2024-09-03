#pragma once

#include <vector>

#include "Script.h"
#include "Curtain.h"
#include "Jukebox.h"

#include "Stage.h"

class Scene : public Script, public Curtain, public Jukebox
{
public:
	Scene(SDL_Renderer* render_target, TTF_Font* font, Inspector* inspector, Stage* stage);

	void update(double delta);
	void draw(SDL_Renderer* render_target);

	void set_player_array(Acteur* player_array, int player_amount);

private:
	Acteur* player_array;
	int player_amount;

	Stage* stage;
};