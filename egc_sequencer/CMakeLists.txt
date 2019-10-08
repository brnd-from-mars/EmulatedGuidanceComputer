add_library(egc_sequencer
        Sequencer.cpp)

target_include_directories(egc_sequencer
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(egc_sequencer egc_memory)
