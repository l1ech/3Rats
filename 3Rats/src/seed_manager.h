#ifndef SEEDMANAGER_H
#define SEEDMANAGER_H

#include <iostream>
#include <cstdlib>

class Seed_manager {
public:
    enum SeedType {
        RANDOM,
        USER_INPUT,
        FIXED_TESTING
    };

    Seed_manager() : seed(0) {}

    uint32_t generateSeed(int seedGenerationType);
    uint32_t worldSeedGeneration(bool value);
    void setSeed(uint32_t newSeed) { seed = newSeed; }
    uint32_t getSeed() const { return seed; }

private:
    uint32_t seed;

    uint32_t generateRandomSeed();
    uint32_t getUserInputSeed();
};

#endif
