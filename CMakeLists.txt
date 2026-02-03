cmake_minimum_required(VERSION 3.10)
project(Tetris LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Find ncurses package (handles linking automatically)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(tetris ${SOURCES})

# Link ncurses library
target_link_libraries(tetris ${CURSES_LIBRARIES})