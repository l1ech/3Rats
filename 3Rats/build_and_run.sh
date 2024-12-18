#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define the build directory (optional, update as needed)
BUILD_DIR="build"

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Navigate to the build directory
cd "$BUILD_DIR"

# Clean previous build files
make clean || echo "No make clean step needed. Skipping."

# Run CMake configuration
cmake ..

# Compile the program
make

pwd

cd "bin"

pwd

EXECUTABLE="./3Rats"

if [ -f "$EXECUTABLE" ]; then
    echo "Starting the program..."
    "$EXECUTABLE"
else
    echo "Error: Executable not found. Ensure the correct executable name is specified in the script."
    echo "Path: $EXECUTABLE"
    exit 1
fi
