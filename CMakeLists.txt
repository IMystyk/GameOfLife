cmake_minimum_required(VERSION 3.17)
project(CGOL)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp Cell.cpp Cell.h Button.cpp Button.h Game.h Game.cpp)

add_executable(CGOL WIN32 ${SOURCES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SFML_ROOT "C:/SFML")
set(SFML_STATIC_LIBRARIES TRUE)


find_package(SFML COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(CGOL sfml-graphics)
endif()
