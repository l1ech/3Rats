#pragma once

#include "Clock.h"
#include <vector>
#include <SDL2/SDL.h>

#include "../../../ui/Fade.h"
#include "../../../ui/Overlay.h"   

#include "../../../init.h"

class Init; // or struct Init;

class Clock_Manager {
private:
    Clock* clocks;  // Store multiple clocks

public:
    Clock_Manager();
    void update_all(double delta);
    void draw_all(SDL_Renderer* renderTarget);

    void init(Init init, Clock *c, Fade *fade, Overlay *overlay, Time *world_time);
    

    Clock* get_clocks();
};
