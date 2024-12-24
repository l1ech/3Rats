#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class FileHandler {
public:
    FileHandler();

    void saveTopoToFile(const std::vector<std::vector<std::pair<std::string, int>>>& map_data);

    void saveMapToFile(const std::vector<std::vector<int>> &map_data);

private:
    std::string mapPath;
    std::string topoPath;
};

#endif // FILEHANDLER_H
