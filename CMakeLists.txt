cmake_minimum_required(VERSION 3.16)

project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -O0")

add_subdirectory(ui)
add_subdirectory(gamelogic)
add_subdirectory(statemachine)
add_subdirectory(stringutils)

add_executable(GameOfLife main.cpp)
target_link_libraries(GameOfLife UI GameLogic Statemachine)