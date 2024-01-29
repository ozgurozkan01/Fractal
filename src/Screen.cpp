#include "Screen.h"
#include "Mandelbrot/Mandelbrot.h"
#include <iostream>

Screen::Screen() :
    isWindowOpen(true)
{
    windowPixels = new uint32_t [windowHeight * windowWidth];
    mandelbrot = new Mandelbrot();
    snowflake = new Snowflake();
    init();
}

Screen::~Screen()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Screen::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialise: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        printf("SDL_Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        printf("SDL_Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC,
                                windowWidth,
                                windowHeight);

    if(texture == nullptr)
    {
        printf("SDL_Texture creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return;
    }
}

void Screen::processEvent()
{
    SDL_Event e;

    while(isWindowOpen)
    {
        update();
        while (SDL_PollEvent(&e))
        {
            if (e.key.type == SDL_QUIT)
            {
                isWindowOpen = false;
            }

            if (e.key.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_E)
            {
                snowflake->createNextGenerationSegments();
            }
        }
    }
}

void Screen::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t pixelColor = 0x00000000;
    pixelColor += red;
    pixelColor <<= 8;
    pixelColor += green;
    pixelColor <<= 8;
    pixelColor += blue;
    pixelColor <<= 8;
    pixelColor += 0xFF;

    windowPixels[(y * windowWidth) + x] = pixelColor;
}

void Screen::update()
{
    drawFractal(1);
}

void Screen::drawFractal(int n)
{
    switch (n)
    {
        /* Mandelbrot */
        case 0:
            SDL_UpdateTexture(texture, nullptr, windowPixels, windowWidth * sizeof(Uint32));
            SDL_RenderClear(renderer); // Clear renderer which render the data its stored.
            SDL_RenderCopy(renderer, texture, nullptr, nullptr); // Fill the renderer via texture
            SDL_RenderPresent(renderer);

            for (int row = 0; row < windowHeight; ++row) {
                for (int column = 0; column < windowWidth; ++column) {
                    uint8_t color = mandelbrot->getMandelbrotPixelColor(column, row, windowWidth, windowHeight);
                    color = color * color * color;
                    setPixel(column, row, 0, color, 0);
                }
            }
            break;

        /* Snowflake */
        case 1:
            if (renderer)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                snowflake->drawSnowflake(renderer);
                SDL_RenderPresent( renderer );
            }
        default:
            break;
    }
}