cmake_minimum_required(VERSION 3.20)
project(CrossyRoad_Tema)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Adăugare FetchContent ---
# Aceasta este magia. CMake va descărca și compila SFML automat.
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1 # Folosim versiunea stabilă
)

FetchContent_MakeAvailable(SFML)
# --- Sfârșit FetchContent ---


# Găsește toate fișierele .cpp (metoda ta simplă)
file(GLOB SOURCES "*.cpp")

# Creează executabilul
add_executable(CrossyRoad_Tema ${SOURCES})

# --- Legare Biblioteci ---
# Acum ne legăm de țintele pe care FetchContent tocmai le-a creat
# (sfml-system, sfml-window, sfml-graphics)
target_link_libraries(CrossyRoad_Tema PRIVATE sfml-system sfml-window sfml-graphics)


# --- Dependințe pentru Linux (Necesar pentru CI) ---
# CI-ul tău rulează pe Ubuntu. SFML pe Linux are nevoie de astea.
find_package(Threads REQUIRED)
target_link_libraries(CrossyRoad_Tema PRIVATE Threads::Threads)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(CrossyRoad_Tema PRIVATE X11)
endif()