project(UI)

add_library(UI ui.cpp)
target_include_directories(UI PUBLIC include)
target_link_libraries(UI GameLogic StringUtils)

