#pragma once

#include <string>
#include <iostream>
#include "../../../ui/Panel.h"

#include "../../../core/Time.h"  // Include the Time header

class Clock : public Panel {
private:
    Time time;  // Private Time object

public:
    Clock();
    void update(double delta);
    void draw(SDL_Renderer* renderTarget);
    void set_time(int hour, int min);
    int get_day();
    bool day_time();
};
