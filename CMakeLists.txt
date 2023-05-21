cmake_minimum_required(VERSION 3.22)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_Install OFF CACHE INTERNAL "")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src)
add_subdirectory(nlohmann_json)
add_subdirectory(Search_Engine_Tst)

target_compile_definitions(search_engine PRIVATE SEARCHENGINE_LIBRARY)

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
