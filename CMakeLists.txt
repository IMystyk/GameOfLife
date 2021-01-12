cmake_minimum_required(VERSION 3.17)
project(CGOL)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp Cell.cpp Cell.h Button.cpp Button.h Game.h Game.cpp)

add_executable(CGOL WIN32 ${SOURCES})

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SFML_ROOT "C:/SFML")

include_directories(headers /usr/include C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(CGOL ${SFML_LIBRARIES})
endif()

# CPack packaging

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# copy dlls

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
