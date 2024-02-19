cmake_minimum_required(VERSION 3.10)
project(MyProjectName)

# Set C++ standard (optional)
set(CMAKE_CXX_STANDARD 11)

# Add your source files
set(SOURCES
    src/main.cpp
    src/other_file.cpp
    # Add more source files as needed
)

# Add an executable target
add_executable(MyExecutable ${SOURCES})

