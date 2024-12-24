// input_handler.h
#pragma once

#include <SDL.h>

#include "../../Acteur.h"  // Make sure to include any necessary classes

#include "../../../ui/Fade.h"
#include "../../../ui/Pause.h"
//#include "core/Texture_Manager.h"

bool handle_key_event(SDL_Event& ev, Acteur* player_array, Acteur* entity_array, int& mode, Fade& fade, Pause& pause);
