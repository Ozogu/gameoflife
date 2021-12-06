project(GameLogic)

add_library(GameLogic gamelogic.cpp)
target_include_directories(GameLogic PUBLIC include)
target_link_libraries(GameLogic StringUtils)
