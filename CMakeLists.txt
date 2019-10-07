cmake_minimum_required(VERSION 3.14)
project(EmulatedGuidanceComputer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(egc_memory)

add_executable(EmulatedGuidanceComputer main.cpp)
target_link_libraries(EmulatedGuidanceComputer egc_memory)
