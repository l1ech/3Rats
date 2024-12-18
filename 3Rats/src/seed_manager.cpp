#include "seed_manager.h"

uint32_t Seed_manager::generateSeed(int seedGenerationType) {
    switch (seedGenerationType) {
    case RANDOM:
        return generateRandomSeed();
    case USER_INPUT:
        return getUserInputSeed();
    case FIXED_TESTING:
        return 1; // Fixed seed for testing
    default:
        std::cerr << "Invalid seed generation type!" << std::endl;
        return 0;
    }
}

uint32_t Seed_manager::generateRandomSeed() {
    // Generate a random seed (you can replace this logic if you want more control)
    return static_cast<uint32_t>(std::rand());
}

uint32_t Seed_manager::getUserInputSeed() {
    uint32_t userSeed;
    std::cout << "Enter a seed: ";
    std::cin >> userSeed;
    return userSeed;
}

uint32_t Seed_manager::worldSeedGeneration(bool value) {
    if (value) {
        return 0; // Default random seed if testing
    } else {
        int type_generation;
        int seed_input;

        std::cout << "What type of generation?" << std::endl;
        std::cout << "random seed: 0" << std::endl;
        std::cout << "user input: 1" << std::endl;
        std::cout << "fix seed (testing): 2" << std::endl;
        std::cin >> type_generation;

        switch (type_generation) {
        case 0:
            seed_input = 0; // Random seed
            break;
        case 1:
            std::cin >> seed_input; // User input for seed
            break;
        case 2:
            seed_input = 0; // Fixed seed for testing
            break;
        default:
            std::cerr << "Invalid choice! Defaulting to random seed." << std::endl;
            seed_input = 0;
            break;
        }
        return seed_input;
    }
}

