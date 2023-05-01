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
find_package(Qt5 COMPONENTS
		 Core
		 Gui
		 Widgets
REQUIRED
)

add_subdirectory(Search_Engine_Tst)
add_subdirectory(nlohmann_json)
add_library(search_engine SHARED ${SOURCE} ${INCLUDE})
#add_executable(search_engine )
target_include_directories (search_engine PUBLIC ${MY_DIRECTORY})
target_link_libraries(search_engine PUBLIC
    nlohmann_json::nlohmann_json
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets)

