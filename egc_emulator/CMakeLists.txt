add_library(egc_emulator
        Emulator.cpp)

target_include_directories(egc_emulator
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(egc_emulator egc_util egc_memory egc_sequencer)