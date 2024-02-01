#include <complex>
#include "Mandelbrot.h"
#include "Zoom.h"
#include "ZoomList.h"
#include "RGB.h"
#include <assert.h>

Mandelbrot::Mandelbrot(int windowWidth, int windowHeight) :
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        fractalPixels(new uint32_t[windowHeight * windowWidth]{0}),
        pixelIterations(new int[windowHeight * windowWidth]{0}),
        histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
        totalIteration(0),
        bGotFirstRange(false)
{};
Mandelbrot::~Mandelbrot()
{
    delete [] histogram;
    delete [] pixelIterations;
    delete [] fractalPixels;
};

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

void Mandelbrot::calculateIteration(ZoomList *zoomList)
{
    // Get the iteration of each pixel and  stored in the array
    for (int row = 0; row < windowHeight; ++row)
    {
        for (int column = 0; column < windowWidth; ++column)
        {
            std::pair<double, double> coords = zoomList->doZoom(column, row);

            // get the iteration of the particular pixel
            int iteration = getIterations(coords.first, coords.second);
            // To find amount of pixel which has particular iteration number.
            if (histogram && iteration != Mandelbrot::MAX_ITERATIONS)
            {
                histogram[iteration]++;
            }
            // Store the whole pixel iterations
            if (pixelIterations)
            {
                pixelIterations[column * windowHeight + row] = iteration;
            }
        }
    }
}

void Mandelbrot::calculateTotalIterations()
{
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
    {
        totalIteration += histogram[i];
    }
}

void Mandelbrot::drawMandelbrot()
{
    for (int row = 0; row < windowHeight; ++row)
    {
        for (int column = 0; column < windowWidth; ++column)
        {
            // Get iteration of particular pixel by using its index
            int iteration = pixelIterations[column * windowHeight + row];
            int range = getRange(iteration);
            int rangeTotal = rangeTotals[range];
            int rangeStart = colorRanges[range];

            RGB& startColor = colors[range];
            RGB& endColor = colors[range+1];
            RGB colorDiff = endColor - startColor;
            // Set RGB colors
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            // Ignore the pixels whose iterations equals to the max iteration
            if (iteration != Mandelbrot::MAX_ITERATIONS)
            {

                int totalPixels = 0;
                for (int i = rangeStart; i <= iteration; ++i)
                {
                    // Find all pixels color hue separately
                    totalPixels += histogram[i];
                }

                red = startColor.red + colorDiff.red * (double)totalPixels/rangeTotal;
                green = startColor.green + colorDiff.green * (double)totalPixels/rangeTotal;
                blue = startColor.blue + colorDiff.blue * (double)totalPixels/rangeTotal;
            }

            setPixel(column, row, red, green, blue);
        }
    }
}

void Mandelbrot::addColorRange(double rangeEnd, const RGB& color)
{
    colorRanges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
    colors.push_back(color);

    if (bGotFirstRange)
    {
        rangeTotals.push_back(0);
    }

    bGotFirstRange = true;
}

void Mandelbrot::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t pixelColor = 0x00000000;
    pixelColor += red;
    pixelColor <<= 8;
    pixelColor += green;
    pixelColor <<= 8;
    pixelColor += blue;
    pixelColor <<= 8;
    pixelColor += 0xFF;

    fractalPixels[(y * windowWidth) + x] = pixelColor;
}

void Mandelbrot::calculateRangeTotals()
{
    int rangeIndex = 0;
    for (int i = 0; i < MAX_ITERATIONS; ++i)
    {
        int pixels = histogram[i];

        if (i >= colorRanges[rangeIndex+1])
        {
            rangeIndex++;
        }

        rangeTotals[rangeIndex] += pixels;
    }

}

int Mandelbrot::getRange(int iterations) const {
    int range = 0;

    for (int i = 1; i < colorRanges.size(); ++i) {
        range = i;

        if (colorRanges[i] > iterations)
        {
            break;
        }
    }

    range--;

    assert(range > -1);
    assert(range < colorRanges.size());

    return range;
}
