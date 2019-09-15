cmake_minimum_required(VERSION 2.8)
project( GameOfLife )
include_directories( /usr/include/SFML/ )
add_executable( GameOfLife main.cpp Tile.cpp)
target_link_libraries( GameOfLife sfml-graphics sfml-window sfml-system )

