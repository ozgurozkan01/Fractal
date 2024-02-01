//
// Created by ozgur on 28/01/2024.
//

#ifndef FRACTAL_MANDELBROT_H
#define FRACTAL_MANDELBROT_H

#include "SDL.h"
#include <vector>

class ZoomList;
class RGB;

class Mandelbrot{
private:
    int windowHeight;
    int windowWidth;
    int totalIteration;

    int* histogram;
    int* pixelIterations;

    std::vector<int> colorRanges;
    std::vector<RGB> colors;
    std::vector<int> rangeTotals;
    bool bGotFirstRange;

public:
    static const int MAX_ITERATIONS = 1000;
    uint32_t * fractalPixels;

    Mandelbrot(int windowWidth, int windowHeight);
    ~Mandelbrot();
    static int getIterations(double x, double y);
    int getRange(int iterations) const;
    void calculateIteration(ZoomList *zoomList);
    void calculateTotalIterations();
    void calculateRangeTotals();
    void drawMandelbrot();
    void addColorRange(double rangeEnd, const RGB& color);
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
};

#endif //FRACTAL_MANDELBROT_H