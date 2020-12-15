cmake_minimum_required(VERSION 3.13)  # CMake version check
project(plusbussim)               # Create project "simple_example"

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(Cmake simulation.c debug.c debug.h node.c node.h trafficlights.c trafficlights.h simbuildinterpreter.c simbuildinterpreter.h)
