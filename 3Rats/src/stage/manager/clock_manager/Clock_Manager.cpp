#include "Clock_Manager.h"

Clock_Manager::Clock_Manager() {
    SDL_Log("[Clock_Manager]: Manager created");
}

void Clock_Manager::update_all(double delta) {
}

void Clock_Manager::draw_all(SDL_Renderer* renderTarget) {
}
void Clock_Manager::init(Init init, Clock *c, Fade *fade, Overlay *overlay, Time *world_time)
{
    if (c == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Clock_Manager]: ERROR: clock is nullptr");
    }

    clocks = c;
    clocks->set_name("Clock");

    init.init_clock(&clocks[0], fade, overlay, world_time);
}

Clock *Clock_Manager::get_clocks()
{
    return clocks;
}
