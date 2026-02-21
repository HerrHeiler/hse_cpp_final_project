cmake_minimum_required(VERSION 3.10) 
project(student-game)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Window Graphics System REQUIRED)

include_directories(include)

add_executable(student-game 
    src/main.cpp 
    src/Game.cpp 
    src/StateManager.cpp 
    src/states/MainMenuState.cpp 
    src/states/CorridorState.cpp
    src/Door.cpp
    src/Student.cpp
    src/World.cpp
    src/ResourceManager.cpp
)

target_include_directories(student-game PRIVATE include)

target_link_libraries(student-game
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)