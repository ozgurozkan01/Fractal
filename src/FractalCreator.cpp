#include "SDL.h"
#include "FractalCreator.h"
#include "ZoomList.h"
#include "Zoom.h"
#include "Mandelbrot.h"
#include "RGB.h"

FractalCreator::FractalCreator(int windowWidth, int windowHeigth) :
    windowWidth(windowWidth),
    windowHeight(windowHeigth),
    zoomlist(new ZoomList(windowWidth, windowHeight))
{
    zoomlist->addZoom(Zoom(windowWidth/2, windowHeight/2, 4.0/windowWidth));
    zoomlist->addZoom(Zoom(295, 202, 0.1));
    zoomlist->addZoom(Zoom(312, 304, 0.1));

    init();
}

FractalCreator::~FractalCreator()
{
    delete mandelbrot;
    delete zoomlist;
}

void FractalCreator::showMandelbrotOnScreen(SDL_Texture* texture, SDL_Renderer* renderer)
{
    if (texture == nullptr || renderer == nullptr || mandelbrot == nullptr) return;

    SDL_UpdateTexture(texture, nullptr, mandelbrot->fractalPixels, windowWidth * sizeof(Uint32));
    SDL_RenderClear(renderer); // Clear renderer which render the data its stored.
    SDL_RenderCopy(renderer, texture, nullptr, nullptr); // Fill the renderer via texture
    SDL_RenderPresent(renderer);

    mandelbrot->drawMandelbrot();
}

void FractalCreator::init()
{
    mandelbrot = new Mandelbrot(windowWidth, windowHeight);
    mandelbrot->addColorRange(0.0, RGB(0, 0, 255));
    mandelbrot->addColorRange(0.05, RGB(255, 99, 71));
    mandelbrot->addColorRange(0.08, RGB(255, 215, 0));
    mandelbrot->addColorRange(1.0, RGB(255, 255, 255));

    mandelbrot->calculateIteration(zoomlist);
    mandelbrot->calculateTotalIterations();
    mandelbrot->calculateRangeTotals();
}

void FractalCreator::drawFractal(SDL_Texture* texture, SDL_Renderer* renderer)
{
    showMandelbrotOnScreen(texture, renderer);
}
