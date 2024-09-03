#pragma once

#include <string>
//#include "Scene.h"

class Inspector
{
public:
    Inspector();

    // Method to process the command and return an integer
    int processCommand(const std::string& message) const;

    //void show_scene(Scene* scene);

private:
    //Scene* scene;
};
