#pragma once

#include "vector"
#include "string"

class Collage
{
private:
    std::vector<std::string> paths;
public:
    Collage();
    ~Collage();

    std::string get_path(int i);
};
