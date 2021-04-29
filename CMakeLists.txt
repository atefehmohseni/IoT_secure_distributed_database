# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# project name
project( distDB )

# flags

# files

# include
include_directories( ./include ./src ./libs/cpp-httplib )

# target
add_executable( client ./src/client.cpp )
add_executable( server ./src/server.cpp )

# external libs

