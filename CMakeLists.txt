cmake_minimum_required(VERSION 3.26)
project(Fractal CXX)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:\\Users\\ozgur\\SDL2-2.28.1\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(Fractal src/main.cpp
        src/Screen.cpp
        src/Screen.h
        src/Mandelbrot.cpp
        src/Mandelbrot.h
        src/Zoom.h
        src/ZoomList.cpp
        src/ZoomList.h
        src/FractalCreator.cpp
        src/FractalCreator.h
        src/RGB.cpp
        src/RGB.h
)
target_link_libraries(Fractal ${SDL2_LIBRARY} )
