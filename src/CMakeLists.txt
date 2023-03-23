cmake_minimum_required(VERSION 3.22)

set (MY_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
set(JSON_Install OFF CACHE INTERNAL "")
set(SOURCE
        main.cpp
        ConverterJSON.cpp
        resources.qrc
        )
set(INCLUDE
        ${MY_DIRECTORY}/ConverterJSON.h
        ${MY_DIRECTORY}/config_exception.h
        )
add_subdirectory(nlohmann_json)
add_executable(search_engine ${SOURCE} ${INCLUDE})
target_include_directories (search_engine PUBLIC ${MY_DIRECTORY})
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)