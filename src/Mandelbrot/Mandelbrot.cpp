#include <complex>
#include "Mandelbrot.h"

Mandelbrot::Mandelbrot() = default;
Mandelbrot::~Mandelbrot() = default;

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