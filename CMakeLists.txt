cmake_minimum_required(VERSION 3.10) 
project(student-game)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)


include_directories(include)

add_executable(student-game 
    src/main.cpp 
    src/Game.cpp 
    src/StateManager.cpp 
    src/states/MainMenuState.cpp 
    src/states/CorridorState.cpp
)

target_link_libraries(student-game sfml-graphics sfml-window sfml-system)