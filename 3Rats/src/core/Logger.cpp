#include "Logger.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Constants.h"
#include <fstream>
#include <cstring>  // For strerror
#include <cerrno>   // For errno

Logger::Logger() {
    // Print the log file path for debugging
    std::cout << "[Logger]: Log file path: " << Main_Constants::DEBUG_PATH << std::endl;

    // Open the log file in write mode to clear any existing content
    std::ofstream logFile(Main_Constants::DEBUG_PATH, std::ios::out | std::ios::trunc);
    if (logFile.is_open()) {
        logFile.close(); // Close the file after clearing
    } else {
        std::cerr << "[Logger]: Failed to open log file for clearing" << std::endl;
    }

    // Redirect SDL logs to the file
    SDL_LogSetOutputFunction(logToFile, this);
}

Logger::~Logger() {
    // No need to close the file here since it's opened and closed in each log operation
}

void Logger::logToFile(void* userdata, int category, SDL_LogPriority priority, const char* message) {
    Logger* logger = static_cast<Logger*>(userdata);

    // Open the log file in append mode
    std::ofstream logFile(Main_Constants::DEBUG_PATH, std::ios::out | std::ios::app);

    // Check if file was opened successfully
    if (!logFile.is_open()) {
        std::cerr << "[Logger]: Failed to open SDL log file! Error: " << strerror(errno) << std::endl;
        return;
    }

    // Check the log priority and handle accordingly
    switch (priority) {
        case SDL_LOG_PRIORITY_VERBOSE:
            logFile << "[VERBOSE]: " << message << "\n";
            break;
        case SDL_LOG_PRIORITY_DEBUG:
            logFile << "[DEBUG]: " << message << "\n";
            break;
        case SDL_LOG_PRIORITY_INFO:
            logFile << "[INFO]: " << message << "\n";
            break;
        case SDL_LOG_PRIORITY_WARN:
            logFile << "[WARN]: " << message << "\n";
            break;
        case SDL_LOG_PRIORITY_ERROR:
            logFile << "[ERROR]: " << message << "\n";
            break;
        case SDL_LOG_PRIORITY_CRITICAL:
            logFile << "[CRITICAL]: " << message << "\n";
            break;
        default:
            logFile << "[UNKNOWN]: " << message << "\n";
            break;
    }

    // Close the file
    logFile.close();
}

void Logger::resetLog() {
    SDL_LogSetOutputFunction(nullptr, nullptr);  // Reset SDL log output function to default
}

void Logger::setLogPriorities() {
    // Set all log categories to only log errors (can be modified based on needs)
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_ERROR);
}

void Logger::setLogCategoryPriority(SDL_LogCategory category, SDL_LogPriority priority) {
    // You can adjust specific categories to different priorities
    SDL_LogSetPriority(category, priority);
}
