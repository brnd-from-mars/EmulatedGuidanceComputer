add_library(egc_memory
        ErasableMemory.cpp
        ErasableMemoryBank.cpp
        ErasableMemoryBankZero.cpp
        FixedMemory.cpp
        FixedMemoryBank.cpp
        Memory.cpp
        MemoryBank.cpp)

target_include_directories(egc_memory
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
