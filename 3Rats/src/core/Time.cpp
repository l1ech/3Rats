#include "Time.h"
#include <SDL.h>
#include <SDL_log.h>

Time::Time()
    : day_counter(0), is_day(true), spacetime(0), min(0), hour(0) {
    SDL_Log("[Time]: Constructor called");
}

void Time::update(double delta) {
    spacetime += delta;
    //SDL_Log("[Time]: spacetime updated to %f", spacetime);

    if (spacetime >= 5) {
        spacetime = 0;
        min++;
        //SDL_Log("[Time]: Minute incremented to %d", min);
    }

    if (min >= 60) {
        min = 0;
        hour++;
        //SDL_Log("[Time]: Hour incremented to %d", hour);
    }

    if (hour >= 24) {
        hour = 0;
        //SDL_Log("[Time]: Day reset, hour set to %d", hour);
    }

    str_time_min = format_time(min);
    str_time_hour = format_time(hour);
}

void Time::set_time(int hour, int min) {
    spacetime = 0;
    this->min = min;
    this->hour = hour;
    //SDL_Log("[Time]: Time set to %d:%d", hour, min);
}

int Time::get_day() {
    //SDL_Log("[Time]: Returning day counter %d", day_counter);
    return day_counter;
}

bool Time::day_time() {
    //SDL_Log("[Time]: Returning is_day value %d", is_day);
    return is_day;
}

std::string Time::format_time(int time_value) {
    std::string formatted_time = std::to_string(time_value);
    if (formatted_time.size() == 1) {
        formatted_time = "0" + formatted_time;
    }
    return formatted_time;
}

std::string Time::get_time_display() {
    return str_time_hour + ":" + str_time_min;
}
