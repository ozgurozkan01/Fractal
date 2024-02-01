cmake_minimum_required(VERSION 3.26)
project(Fractal CXX)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:\\Users\\ozgur\\SDL2-2.28.1\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(Fractal src/main.cpp
        src/Editor/Screen.cpp
        src/Editor/Screen.h
        src/Fractal/Mandelbrot/Mandelbrot.cpp
        src/Fractal/Mandelbrot/Mandelbrot.h
        src/Fractal/Snowflake/Snowflake.cpp
        src/Fractal/Snowflake/Snowflake.h
        src/Fractal/Snowflake/Segment.cpp
        src/Fractal/Snowflake/Segment.h
        src/Fractal/Mandelbulb/Mandelbulb.cpp
        src/Fractal/Mandelbulb/Mandelbulb.h
        src/Editor/Zoom.h
        src/Editor/ZoomList.cpp
        src/Editor/ZoomList.h
        src/Fractal/FractalCreator.cpp
        src/Fractal/FractalCreator.h
        src/Editor/RGB.cpp
        src/Editor/RGB.h
)
target_link_libraries(Fractal ${SDL2_LIBRARY} )
