cmake_minimum_required(VERSION 3.10)
project(3Rats)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure debug symbols are generated
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Enable compile_commands.json for debugging tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add all .cpp files in the src directory
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# Add all .h files in the src directory
file(GLOB_RECURSE HEADERS "src/*.h")

# Find SDL2 and related libraries
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)

# Ensure SDL2 include directories are included
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Add the executable
add_executable(3Rats ${SOURCES})

# Link SDL2 libraries
target_link_libraries(3Rats 
    PRIVATE SDL2::SDL2 
    SDL2::SDL2main 
    SDL2_mixer::SDL2_mixer 
    SDL2_ttf::SDL2_ttf 
    SDL2_image::SDL2_image
)

# Specify binary output directory
set_target_properties(3Rats PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Optional: Add debug information for clarity
message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
