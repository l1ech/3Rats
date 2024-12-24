#include "seed_manager.h"
#include <random>

#include <SDL_log.h>

SDL_LogCategory customCategory = SDL_LOG_CATEGORY_APPLICATION;

uint32_t Seed_manager::generateSeed(int seedGenerationType) {
    switch (seedGenerationType) {
        case RANDOM:
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Generating random seed.");
            return generateRandomSeed();
        case USER_INPUT:
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Waiting for user input seed.");
            return getUserInputSeed();
        case FIXED_TESTING:
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Using fixed seed for testing.");
            return 1; // Fixed seed for testing
        default:
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Invalid seed generation type!");
            return 0;
    }
}

uint32_t Seed_manager::generateRandomSeed() {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Generating random seed using std::random_device.");
    // Use random_device or mt19937 for better randomness
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);
    uint32_t seed = dist(gen);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Generated random seed: %u", seed);
    return seed;
}

uint32_t Seed_manager::getUserInputSeed() {
    uint32_t userSeed;
    std::cout << "[Seed_Manager]: Enter a seed: ";
    while (!(std::cin >> userSeed)) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Invalid input. Prompting for a valid seed.");
        std::cout << "[Seed_Manager]: Invalid input. Please enter a valid seed: ";
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: User entered seed: %u", userSeed);
    return userSeed;
}

uint32_t Seed_manager::worldSeedGeneration(bool value) {
    if (value) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Using default random seed for testing.");
        return 0; // Default random seed if testing
    } else {
        int type_generation;
        uint32_t seed_input = 0;

        // Display options to the user
        std::cout << "[Seed_Manager]: Please select the type of generation:\n";
        std::cout << "  0 - Random seed\n";
        std::cout << "  1 - User input\n";
        std::cout << "  2 - Fixed seed (for testing)\n";
        //std::cout << "Enter your choice (0, 1, or 2): ";

        type_generation = 0;

        // Validate input and assign appropriate seed
        switch (type_generation) {
            case 0:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: User chose random seed.");
                seed_input = generateRandomSeed(); // Use random seed
                break;
            case 1:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: User chose input seed.");
                seed_input = getUserInputSeed(); // Get user input seed
                break;
            case 2:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: User chose fixed seed for testing.");
                seed_input = 1; // Fixed seed for testing
                break;
            default:
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Invalid choice! Defaulting to random seed.");
                seed_input = generateRandomSeed();
                break;
        }
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Seed_Manager]: Generated seed: %u", seed_input);
        return seed_input;
    }
}
