cmake_minimum_required(VERSION 3.10)
project(3Rats)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure debug symbols are generated
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Enable compile_commands.json for debugging tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add all .cpp files in the src directory
file(GLOB SOURCES
    "src/*.cpp"       
    "src/input/*.cpp" 
    "src/game/*.cpp"
    "src/game/stage/*.cpp"
    "src/game/stage/factory/map_factory/*.cpp"
    "src/game/stage/factory/map_factory/map_types/*.cpp"
    "src/game/stage/manager/door_manager/*.cpp"
    "src/game/stage/manager/item_manager/*.cpp"
    "src/game/stage/manager/tile_manager/*.cpp"
    "src/audio/*.cpp"
    "src/core/*.cpp"
    "src/ui/*.cpp"
)
# Add all .h files in the src directory
file(GLOB HEADERS "src/*.h")

# Find SDL2 libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

# Add executable
add_executable(3Rats ${SOURCES})

# Link libraries
target_link_libraries(3Rats PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)

# Specify binary output directory
set_target_properties(3Rats PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
