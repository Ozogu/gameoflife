project(Statemachine)

add_library(Statemachine statemachine.cpp)
target_include_directories(Statemachine PUBLIC include)
target_link_libraries(Statemachine UI GameLogic)
