cmake_minimum_required(VERSION 3.10)
project(student-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)


include_directories(include)


add_executable(student-game 
    src/main.cpp 
    src/Game.cpp 
    src/StateManager.cpp 
    src/states/MainMenuState.cpp 
    src/states/CorridorState.cpp
    src/ResourceManager.cpp
    src/Student.cpp
    src/Door.cpp
    src/World.cpp
)

target_include_directories(student-game PRIVATE include)

target_link_libraries(student-game
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)