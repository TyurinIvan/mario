cmake_minimum_required(VERSION 2.4)

project(GAME)

#list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(SFML REQUIRED COMPONENTS graphics window system) 
include_directories(${SFML_INCLUDE_DIR})


add_executable(main  mario.cpp)	
#add_executable(game_test mario.cpp  game_test.cpp)


target_link_libraries(main PUBLIC sfml-window sfml-graphics) 
#target_link_libraries(game_test PUBLIC sfml-window sfml-graphics)


enable_testing()
#add_test(game_test game_test)