#include "Inspector.h"

Inspector::Inspector()
{
}

int Inspector::processCommand(const std::string& message) const
{
    if (message == "/play")
    {
        return 1;  // Command to start the music
    }
    else if (message == "/pause")
    {
        return 2;  // Command to pause the music
    } 
    else if (message == "/tps")
    {
        return 3;
    }
    
    return 0;  // No command recognized
}

/*
void Inspector::show_scene(Scene* scene_p)
{
    scene = scene_p;
}

*/
