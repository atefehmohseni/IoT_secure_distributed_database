# cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# compiler
set( CMAKE_C_COMPILER gcc-8 )
set( CMAKE_CXX_COMPILER g++-8 )

# project name
project( distDB )

# dependencies
set( THREADS_PREFER_PTHREAD_FLAG ON )
find_package( Threads REQUIRED )
find_package( OpenSSL REQUIRED )
set( SSL TRUE )

add_custom_command( OUTPUT bcrypt
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/libbcrypt )
set_property(SOURCE src/server.cpp APPEND PROPERTY OBJECT_DEPENDS bcrypt)

# flags

# files

# include
include_directories( include src libs/httplib libs/json libs/base64 )

# subdirectories
include_directories( libs/libbcrypt )
# link_directories( libs/libbcrypt )

# target

add_executable( client src/client.cpp )
add_executable( server src/server.cpp )

# link with pthread, openssl, filesystem
target_link_libraries( client PUBLIC
        $<$<BOOL:${SSL}>:OpenSSL::SSL>
        $<$<BOOL:${SSL}>:OpenSSL::Crypto>
        stdc++fs
        pthread )
target_link_libraries( server PUBLIC
        ${CMAKE_SOURCE_DIR}/libs/libbcrypt/bcrypt.a
        $<$<BOOL:${SSL}>:OpenSSL::SSL>
        $<$<BOOL:${SSL}>:OpenSSL::Crypto>
        Threads::Threads
        stdc++fs )

# use c++17
set_target_properties( client PROPERTIES CXX_STANDARD 17 )
set_target_properties( server PROPERTIES CXX_STANDARD 17 )

# external libs

