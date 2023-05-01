cmake_minimum_required(VERSION 3.22)
project(search_engine)

set(CMAKE_PREFIX_PATH "D:/QtP/5.15.2/mingw81_64/lib/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_ENABLE_EXPORTS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(src)

target_compile_definitions(search_engine PRIVATE SEARCHENGINE_LIBRARY)
