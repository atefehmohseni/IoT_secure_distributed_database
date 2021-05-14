# cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# project name
project( distDB )

# dependencies
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# flags

# files

# include
include_directories( ./include ./src ./libs/httplib ./libs/json )

# target
add_executable( client ./src/client.cpp )
add_executable( server ./src/server.cpp )

# link server with pthread
target_link_libraries(server PRIVATE Threads::Threads)

# external libs

