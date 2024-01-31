cmake_minimum_required(VERSION 3.26)
project(Fractal CXX)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:\\Users\\ozgur\\SDL2-2.28.1\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(Fractal src/main.cpp
        src/Editor/Screen.cpp
        src/Editor/Screen.h
        src/Mandelbrot/Mandelbrot.cpp
        src/Mandelbrot/Mandelbrot.h
        src/Snowflake/Snowflake.cpp
        src/Snowflake/Snowflake.h
        src/Snowflake/Segment.cpp
        src/Snowflake/Segment.h
        src/Mandelbulb/Mandelbulb.cpp
        src/Mandelbulb/Mandelbulb.h
        src/Editor/Zoom.cpp
        src/Editor/Zoom.h
)
target_link_libraries(Fractal ${SDL2_LIBRARY} )
