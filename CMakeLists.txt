cmake_minimum_required(VERSION 3.20)
project(CrossyRoad_Tema)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Adăugare FetchContent ---
# CMake va descărca și compila SFML automat.
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1 # Folosim versiunea stabilă
)

FetchContent_MakeAvailable(SFML)
# --- Sfârșit FetchContent ---


# Găsește toate fișierele .cpp
file(GLOB SOURCES "*.cpp")

# Numele executabilului (trebuie să se potrivească cu cel din cmake.yml)
set(MAIN_EXECUTABLE_NAME "CrossyRoad_Tema")
add_executable(${MAIN_EXECUTABLE_NAME} ${SOURCES})


# --- Legare Biblioteci ---
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-system sfml-window sfml-graphics)


# --- Dependințe pentru Linux (Necesar pentru CI) ---
find_package(Threads REQUIRED)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE Threads::Threads)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
endif()

# ================================================
# --- REGULA DE INSTALARE (ASTA LIPSEA) ---
# ================================================
# Acest pas îi spune lui CMake ce să copieze în timpul pasului "Install"
# "bin" este folderul ${{ env.BIN_DIR }} din fișierul tău cmake.yml

install(TARGETS ${MAIN_EXECUTABLE_NAME}
        RUNTIME DESTINATION bin
)