#include "Clock.h"
#include <iostream> // Include for debugging messages

Clock::Clock()
{
    day_counter = 0;
    is_day = true;
    spacetime = 0;
    min = 0;
    hour = 0;
    std::cout << "[Clock]: Constructor called" << std::endl;
}

void Clock::update(double delta)
{
    spacetime += delta;
    std::cout << "[Clock]: spacetime updated to " << spacetime << std::endl;

    if (spacetime >= 5)
    {
        spacetime = 0;
        min++;
        std::cout << "[Clock]: Minute incremented to " << min << std::endl;
    }

    if (min >= 60)
    {
        min = 0;
        hour++;
        std::cout << "[Clock]: Hour incremented to " << hour << std::endl;
    }

    if (hour >= 24)
    {
        hour = 0;
        std::cout << "[Clock]: Day reset, hour set to " << hour << std::endl;
    }

    str_time_min = std::to_string((int)min);
    str_time_hour = std::to_string((int)hour);

    if (str_time_min.size() == 1)
    {
        str_time_min = "0" + str_time_min;
    }

    if (str_time_hour.size() == 1)
    {
        str_time_hour = "0" + str_time_hour;
    }

    display_text = str_time_hour + ":" + str_time_min;
    std::cout << "[Clock]: Current time is " << display_text << std::endl;

    Panel::update();

    if (hour == 22 && min == 0 && is_day)
    {
        day_counter++;
        std::cout << "[Clock]: Day " << day_counter << " passed. It's time to sleep now!" << std::endl;
        is_day = false;
    }
    else if (hour == 22 && min == 1 && !is_day)
    {
        is_day = true;
        set_time(16, 30);
        std::cout << "[Clock]: New day started, time set to 16:30" << std::endl;
    }
}

void Clock::draw(SDL_Renderer* renderTarget)
{
    std::cout << "[Clock]: Drawing clock" << std::endl;
    Panel::draw(renderTarget);
}

void Clock::set_time(int hour, int min)
{
    spacetime = 0;
    this->min = min;
    this->hour = hour;
    std::cout << "[Clock]: Time set to " << hour << ":" << min << std::endl;
}

int Clock::get_day() // namechange get_day_number
{
    std::cout << "[Clock]: Returning day counter " << day_counter << std::endl;
    return day_counter;
}

bool Clock::day_time() // namechange get_day_value
{
    std::cout << "[Clock]: Returning is_day value " << is_day << std::endl;
    return is_day;
}
