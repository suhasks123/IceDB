cmake_minimum_required( VERSION 3.0 )

project( IceDB )

include_directories( ./include ./src )
add_executable( ice ./src/IceDB.cc ./src/main.cc )