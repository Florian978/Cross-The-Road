cmake_minimum_required(VERSION 3.20)
project(CrossyRoad_Tema)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

file(GLOB SOURCES "*.cpp")

add_executable(CrossyRoad_Tema ${SOURCES})

target_link_libraries(CrossyRoad_Tema PRIVATE sfml-system sfml-window sfml-graphics)

target_compile_options(CrossyRoad_Tema PRIVATE -Wall -Wextra -Wpedantic)