cmake_minimum_required(VERSION 3.10) 
project(student-game)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#for mac os
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")
find_package(SFML 3 COMPONENTS Window Graphics System REQUIRED)


#for linux 
# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 3.0.0
# )
# FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

add_executable(student-game 
    src/main.cpp 
    src/Game.cpp 
    src/StateManager.cpp 
    src/states/MainMenuState.cpp 
    src/states/RoomState.cpp 
    src/states/CorridorState.cpp 
    src/Student.cpp
    src/World.cpp
    src/ResourceManager.cpp
    src/PetStudent.cpp
)

target_include_directories(student-game PRIVATE include)
target_link_libraries(student-game
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)


enable_testing()

add_executable(tests
    tests/test_resource_manager.cpp
    src/ResourceManager.cpp
)


target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System
    GTest::gtest_main
)

target_compile_definitions(tests PRIVATE 
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

include(GoogleTest)
gtest_discover_tests(tests)
