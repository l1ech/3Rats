// input_handler.h
#pragma once

#include <SDL.h>

#include "stage/manager/acteur_manager/Acteur.h"  // Make sure to include any necessary classes

#include "ui/Fade.h"
#include "ui/Pause.h"
//#include "core/Texture_Manager.h"

void handle_key_event(SDL_Event& ev, Acteur* player_array, int player_amount, Acteur* entity_array, int& mode, Fade& fade, Pause& pause);
