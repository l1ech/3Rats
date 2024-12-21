#pragma once

#include <string>
#include <iostream>

class Time {
private:
    bool is_day;
    double spacetime;
    int min;
    int hour;
    int day_counter;
    std::string str_time_min;
    std::string str_time_hour;

public:
    Time();

    void update(double delta);
    void set_time(int hour, int min);
    int get_day();
    bool day_time();
    
    // Utility function to format time
    std::string format_time(int time_value);
    std::string get_time_display();
};
