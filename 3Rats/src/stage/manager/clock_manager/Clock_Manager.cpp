#include "Clock_Manager.h"

Clock_Manager::Clock_Manager() {
    std::cout << "[Clock_Manager]: Manager created" << std::endl;
}

void Clock_Manager::update_all(double delta) {
}

void Clock_Manager::draw_all(SDL_Renderer* renderTarget) {
}

void Clock_Manager::init(Init init, Clock *c, Fade *fade, Overlay *overlay, Time *world_time)
{
    if (c == nullptr)
    {
        std::cout << "[CM]: ERROR: clock is nullptr" << std::endl;
    }
    clocks = c;
    clocks->set_name("TEST");

    init.init_clock(&clocks[0], fade, overlay, world_time);
}

Clock *Clock_Manager::get_clocks()
{
    return clocks;
}
