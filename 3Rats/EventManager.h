#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <unordered_map>
#include <functional>
#include <SDL.h>

// Forward declarations of your classes
class Player;
class Entity;
class Button;
class Chest;
class Pause;

class EventManager {
private:
    std::unordered_map<SDL_Keycode, std::function<void()>> keyHandlers;

    // References or pointers to the objects you need
    Player* player_array;
    Entity* entity_array;
    Button& button;
    Chest& chest;
    Pause& pause;
    bool& isRunning;

public:
    // Constructor with parameters to initialize the references/pointers
    EventManager(Player* player_array, Entity* entity_array,
        Button& button, Chest& chest, Pause& pause, bool& isRunning);

    void handleEvent(SDL_Event& ev);
};

#endif // EVENTMANAGER_H
