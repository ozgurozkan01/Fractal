//
// Created by ozgur on 28/01/2024.
//

#include <complex>
#include "Mandelbrot.h"

Mandelbrot::Mandelbrot()
= default;

Mandelbrot::~Mandelbrot()
= default;

int Mandelbrot::getIterations(double x, double y)
{
    int currentIteration = 0;
    std::complex<double> z = 0;
    std::complex<double> c(x, y);

    while (currentIteration < MAX_ITERATIONS)
    {
        z = z*z + c;

        if (abs(z) > 2) { break; }
        currentIteration++;
    }

    return currentIteration;
}

uint8_t Mandelbrot::getMandelbrotPixelColor(int& column, int& row, const int& windowWidth, const int& windowHeight)
{
    int slideToRight = 125;
    double xFractal = (column - windowWidth / 2 -slideToRight) * (2.0 / windowHeight);
    double yFractal = (row - windowHeight / 2) * (2.0 / windowHeight);

    int iteration = Mandelbrot::getIterations(xFractal, yFractal);
    uint8_t color = (uint8_t)(256 * (double)iteration / Mandelbrot::MAX_ITERATIONS);

    return color;
}