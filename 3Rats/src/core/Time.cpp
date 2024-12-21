#include "Time.h"
#include <iostream>

Time::Time()
    : day_counter(0), is_day(true), spacetime(0), min(0), hour(0) {
    std::cout << "[Time]: Constructor called" << std::endl;
}

void Time::update(double delta) {
    spacetime += delta;
    std::cout << "[Time]: spacetime updated to " << spacetime << std::endl;

    if (spacetime >= 5) {
        spacetime = 0;
        min++;
        std::cout << "[Time]: Minute incremented to " << min << std::endl;
    }

    if (min >= 60) {
        min = 0;
        hour++;
        std::cout << "[Time]: Hour incremented to " << hour << std::endl;
    }

    if (hour >= 24) {
        hour = 0;
        std::cout << "[Time]: Day reset, hour set to " << hour << std::endl;
    }

    str_time_min = format_time(min);
    str_time_hour = format_time(hour);
}

void Time::set_time(int hour, int min) {
    spacetime = 0;
    this->min = min;
    this->hour = hour;
    std::cout << "[Time]: Time set to " << hour << ":" << min << std::endl;
}

int Time::get_day() {
    std::cout << "[Time]: Returning day counter " << day_counter << std::endl;
    return day_counter;
}

bool Time::day_time() {
    std::cout << "[Time]: Returning is_day value " << is_day << std::endl;
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
