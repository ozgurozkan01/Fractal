//
// Created by ozgur on 28/01/2024.
//

#ifndef FRACTAL_MANDELBROT_H
#define FRACTAL_MANDELBROT_H

#include "SDL.h"

class Mandelbrot{
public:
    static const int MAX_ITERATIONS = 1000;

    Mandelbrot();
    ~Mandelbrot();
    static int getIterations(double x, double y);
    uint8_t getMandelbrotPixelColor(int& column, int& row, const int& windowWidth, const int& windowHeight);
};


#endif //FRACTAL_MANDELBROT_H