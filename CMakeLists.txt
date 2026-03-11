cmake_minimum_required(VERSION 3.10) 
project(student-game)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#for mac os
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
find_package(SFML 3 COMPONENTS Window Graphics System REQUIRED)


#for linux 
# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 3.0.0
# )
# FetchContent_MakeAvailable(SFML)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

add_library(game_core STATIC
    src/Game.cpp 
    src/StateManager.cpp 
    src/states/MainMenuState.cpp 
    src/states/CorridorState.cpp
    src/states/RoomState.cpp
    src/Student.cpp
    src/World.cpp
    src/ResourceManager.cpp
)

target_link_libraries(game_core PUBLIC SFML::Graphics SFML::Window SFML::System)
target_include_directories(game_core PUBLIC include)

add_executable(student-game src/main.cpp)
target_link_libraries(student-game PRIVATE game_core)

enable_testing()

add_executable(run_tests 
    tests/test_state_manager.cpp
    tests/test_world_rooms.cpp
    tests/test_world_time.cpp
)

target_link_libraries(run_tests PRIVATE game_core gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)