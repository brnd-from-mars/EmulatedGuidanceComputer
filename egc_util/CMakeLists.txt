add_library(egc_util
        FileSystem.cpp
        StringUtil.cpp)

target_include_directories(egc_util
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)