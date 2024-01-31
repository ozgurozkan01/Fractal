//
// Created by ozgur on 28/01/2024.
//

#ifndef FRACTAL_SCREEN_H
#define FRACTAL_SCREEN_H

#include "SDL.h"
#include "../Mandelbrot/Mandelbrot.h"
#include "../Snowflake/Snowflake.h"

class Screen
{
private:
    const int windowWidth = 1000;
    const int windowHeight = 800;
    const char* windowName = "Fractal_Simulation";

    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
    uint32_t * windowPixels;

    bool isWindowOpen;

    Mandelbrot* mandelbrot;
    Snowflake* snowflake;

    int* histogram;
    int* pixelIterations;

public:

    Screen();
    ~Screen();

    void init();
    void processEvent();
    void drawFractal(int n);
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    void drawMandelbrot();
    void drawSnowflake();
};

#endif //FRACTAL_SCREEN_H
