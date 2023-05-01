cmake_minimum_required(VERSION 3.5)

project(EngineTst LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EngineTst tst_enginetst.cpp)
add_test(NAME EngineTst COMMAND EngineTst)

target_link_libraries(EngineTst PUBLIC search_engine)
target_link_libraries(EngineTst PRIVATE Qt${QT_VERSION_MAJOR}::Test)

