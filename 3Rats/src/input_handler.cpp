// input_handler.cpp
#include "input_handler.h"
#include <iostream>  // For debug output if needed

void handle_key_event(SDL_Event& ev, Acteur* player_array, Acteur* entity_array, int& mode, Fade& fade, Pause& pause, int player_amount) {
    switch (ev.key.keysym.sym) {
        case SDLK_SPACE:
            mode++;
            if (mode == 2) mode = 0;
            break;
        case SDLK_1:
            //texture = LoadTexture(collage.get_path(8), renderTarget);
            break;
        case SDLK_u:
            for (int i = 0; i < player_amount; i++) {
                player_array[i].use_item();
                player_array[i].set_enter(false);
            }
            break;
        case SDLK_r:
            for (int i = 0; i < player_amount; i++) {
                player_array[i].teleport_to_entrence();
                player_array[i].set_enter(false);
            }
            break;
        case SDLK_o:
            entity_array[0].teleport_to_entrence();
            break;
        case SDLK_p:
            player_array[1].place_item();
            player_array[2].place_item();
            player_array[0].set_enter(false);
            break;
        case SDLK_n:
            for (int i = 0; i < player_amount; i++) {
                player_array[i].set_has_goal(false);
                player_array[i].set_enter(false);
            }
            break;
        case SDLK_e:
            player_array[0].set_enter(true);
            break;
        case SDLK_t:
            std::cout << "[input_handler]: tp next room" << std::endl;
            break;
        case SDLK_z:
            std::cout << "[input_handler]: tp prev room" << std::endl;
            break;
        case SDLK_m:
            pause.in();
            break;
        case SDLK_l:
            pause.out();
            break;
        case SDLK_0:
            break;
    }
}
