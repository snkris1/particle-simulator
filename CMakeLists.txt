cmake_minimum_required(VERSION 3.22.1)
set(PROJECT_NAME ParticleSimulator)
project(${PROJECT_NAME})

# Automatically include all source files in the src directory
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp")

# Find SFML
find_package(SFML 2.5 REQUIRED COMPONENTS network audio graphics window system)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

