cmake_minimum_required(VERSION 3.20)
project(CrossyRoad_Tema)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)


file(GLOB SOURCES "*.cpp")

add_executable(CrossyRoad_Tema ${SOURCES})

target_link_libraries(CrossyRoad_Tema PRIVATE sfml-system sfml-window sfml-graphics)

find_package(Threads REQUIRED)
target_link_libraries(CrossyRoad_Tema PRIVATE Threads::Threads)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(CrossyRoad_Tema PRIVATE X11)
endif()