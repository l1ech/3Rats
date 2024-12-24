#include "FileHandler.h"
#include "../../../core/Constants.h"

FileHandler::FileHandler() : topoPath(Main_Constants::TOPO_FILE), mapPath(Main_Constants::MAP_FILE_PATH) {}

void FileHandler::saveTopoToFile(const std::vector<std::vector<std::pair<std::string, int>>>& map_data) {
    std::string filename = topoPath + "topography.txt";

    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Iterate through the 2D map and write each row to the file
    for (const auto& row : map_data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i].first;
            if (i != row.size() - 1) {
                outFile << " ";  // Separate elements in the row with a space
            }
        }
        outFile << std::endl;  // Newline after each row
    }

    outFile.close();
    std::cout << "Topologhy saved successfully to " << filename << std::endl;
}

void FileHandler::saveMapToFile(const std::vector<std::vector<int>> &map_data)
{                
        std::ostringstream oss;
        oss << index;  // Convert index to string
        std::string filename = mapPath + "map_" + oss.str() + ".txt";

        std::ofstream outFile(filename);

        if (!outFile) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }

        // Iterate through the 2D map and write each row to the file
        for (const auto& row : map_data) {
            for (size_t i = 0; i < row.size(); ++i) {
                outFile << row[i];
                if (i != row.size() - 1) {
                    outFile << " ";  // Separate elements in the row with a space
                }
            }
            outFile << std::endl;  // Newline after each row
        }

        outFile.close();

        std::cout << "Map saved successfully to " << filename << std::endl;
}