#include "Clock.h"
#include <iostream>
Clock::Clock() {
    SDL_Log("[Clock]: Constructor called");
}

void Clock::update(double delta) {
    time->update(delta);  // Delegate time update to the Time object
    //SDL_Log("[Clock]: Current time is %s", time->get_time_display().c_str());

    Panel::update();

    if (time->day_time() && time->get_day() == 0 && time->get_time_display() == "22:00") {
        SDL_Log("[Clock]: Day %d passed. It's time to sleep now!", time->get_day());
        time->set_time(16, 30);
    } else if (!time->day_time() && time->get_time_display() == "22:01") {
        SDL_Log("[Clock]: New day started, time set to 16:30");
        time->set_time(16, 30);
    }
}

void Clock::draw(SDL_Renderer* renderTarget) {
    //SDL_Log("[Clock]: Drawing clock");
    Panel::draw(renderTarget);
}

void Clock::set_time(int hour, int min) {
    time->set_time(hour, min);  // Delegate setting time to the Time object
}

int Clock::get_day() {
    return time->get_day();  // Delegate getting day to the Time object
}

bool Clock::day_time() {
    return time->day_time();  // Delegate checking if it's day to the Time object
}

void Clock::set_timer(Time &world_time)
{
    time = &world_time;  
}

void Clock::set_renderer(SDL_Renderer *render_target)
{
    Body::set_surface(render_target);
    Text::set_renderer(render_target);

}
