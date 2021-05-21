# cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# compiler
set(CMAKE_C_COMPILER gcc-8)
set(CMAKE_CXX_COMPILER g++-8)

# project name
project( distDB )

# dependencies
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# flags

# files

# include
include_directories( ./include ./src ./libs/httplib ./libs/json )

# target
add_executable( client ./src/client.cpp )
add_executable( server ./src/server.cpp )

# link server with pthread
target_link_libraries(client PRIVATE OpenSSL::SSL)
target_link_libraries(server PRIVATE Threads::Threads OpenSSL::SSL stdc++fs)

# use c++17
set_target_properties(client PROPERTIES CXX_STANDARD 17 )
set_target_properties(server PROPERTIES CXX_STANDARD 17 )

# external libs

