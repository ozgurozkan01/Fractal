cmake_minimum_required(VERSION 3.26)
project(Fractal CXX)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:\\Users\\ozgur\\SDL2-2.28.1\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(Fractal main.cpp
        Screen.cpp
        Screen.h)
target_link_libraries(Fractal ${SDL2_LIBRARY} )
