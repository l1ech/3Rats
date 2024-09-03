/*#include "EventManager.h"
#include <iostream>

// Assuming Player, Entity, Button, Chest, and Pause are defined elsewhere

EventManager::EventManager(Player* player_array, Entity* entity_array,
    Button& button, Chest& chest, Pause& pause, bool& isRunning)
    : player_array(player_array), entity_array(entity_array),
    button(button), chest(chest), pause(pause), isRunning(isRunning) {

    keyHandlers[SDLK_u] = [this]() {
        player_array[0].use_prop();
        player_array[1].use_prop();
        player_array[2].use_prop();
        player_array[0].set_enter(false);
    };

    keyHandlers[SDLK_r] = [this]() {
        player_array[0].teleport_to_entrence();
        player_array[1].teleport_to_entrence();
        player_array[2].teleport_to_entrence();
        player_array[0].set_enter(false);
        player_array[1].set_enter(false);
        player_array[2].set_enter(false);
    };

    keyHandlers[SDLK_o] = [this]() {
        entity_array[0].teleport_to_entrence();
    };

    keyHandlers[SDLK_p] = [this]() {
        player_array[1].place_prop();
        player_array[2].place_prop();
        player_array[0].set_enter(false);
    };

    keyHandlers[SDLK_n] = [this]() {
        player_array[1].set_has_goal(false);
        player_array[2].set_has_goal(false);
        player_array[0].set_enter(false);
    };

    keyHandlers[SDLK_e] = [this]() {
        player_array[0].set_enter(true);
    };

    keyHandlers[SDLK_t] = [this]() {
        chest.get_prop();
    };

    keyHandlers[SDLK_z] = [this]() {
        std::cout << "tp prev room" << std::endl;
    };

    keyHandlers[SDLK_ESCAPE] = [this]() {
        pause.toggle();
    };

    keyHandlers[SDLK_q] = [this]() {
        isRunning = false;
    };
}

void EventManager::handleEvent(SDL_Event& ev) {
    if (ev.type == SDL_KEYDOWN) {
        auto it = keyHandlers.find(ev.key.keysym.sym);
        if (it != keyHandlers.end()) {
            it->second();  // Call the associated function
        }
    }
}
*/