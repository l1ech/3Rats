#ifndef LOGGER_H
#define LOGGER_H

#include <SDL2/SDL.h>
#include <fstream>
#include <cstring>  // For strerror
#include <cerrno>   // For errno
#include "Constants.h"

class Logger {
public:
    // Constructor and Destructor
    Logger();
    ~Logger();

    // Function to log SDL messages to file
    static void logToFile(void* userdata, int category, SDL_LogPriority priority, const char* message);

    // Function to reset the SDL log output function
    void resetLog();

    // Function to set all log priorities to errors
    void setLogPriorities();

    // Function to set priority for a specific log category
    void setLogCategoryPriority(SDL_LogCategory category, SDL_LogPriority priority);

private:
    // Private member to hold the log file path (optional if you need to store the file name in the object)
    const std::string logFilePath = Main_Constants::DEBUG_PATH;
};

#endif // LOGGER_H
