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

set(MAIN_EXECUTABLE_NAME "CrossyRoad_Tema")
add_executable(${MAIN_EXECUTABLE_NAME} ${SOURCES})


target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-system sfml-window sfml-graphics)


find_package(Threads REQUIRED)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE Threads::Threads)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
endif()

install(TARGETS ${MAIN_EXECUTABLE_NAME}
        RUNTIME DESTINATION bin
)


if(APPLE)
    install(FILES launcher.command
            DESTINATION bin
    )
endif()