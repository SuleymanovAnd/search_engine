cmake_minimum_required(VERSION 3.20)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_Install OFF CACHE INTERNAL "")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (MY_DIRECTORY ${CMAKE_SOURCE_DIR}/include)

set(SOURCE
        ${CMAKE_SOURCE_DIR}/src/SearchServer.cpp
        ${CMAKE_SOURCE_DIR}/src/InvertedIndex.cpp
        ${CMAKE_SOURCE_DIR}/src/ConverterJSON.cpp
        )
set(INCLUDE
        ${MY_DIRECTORY}/ConverterJSON.h
        ${MY_DIRECTORY}/config_exception.h
        ${MY_DIRECTORY}/InvertedIndex.h
        ${MY_DIRECTORY}/SearchServer.h
        )

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Test
        Concurrent
        REQUIRED
        )

add_library(${PROJECT_NAME}_lib STATIC ${SOURCE} ${INCLUDE})
target_link_libraries(${PROJECT_NAME}_lib PUBLIC
        nlohmann_json::nlohmann_json
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Test
        Qt5::Concurrent)
target_include_directories(${PROJECT_NAME}_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (${PROJECT_NAME}_lib PUBLIC ${MY_DIRECTORY})



add_subdirectory(src)
add_subdirectory(nlohmann_json)
add_subdirectory(Search_Engine_Tst)

target_compile_definitions(search_engine_lib PRIVATE SEARCHENGINE_LIBRARY)

add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/config)
    file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/config/config.json "{
        \"config\": {
        \"name\": \"SkillboxSearchEngine\",
        \"version\": \"0.1\",
        \"max_responses\": 5
      },
      \"files\": []
      }")

endif()

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/resources)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resources)
endif()

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/answers)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/answers)
endif()

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/requests)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/requests/requests.json "{
        \"requests\": [

        ]
      }")
endif()
