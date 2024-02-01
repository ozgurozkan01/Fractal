#include "Screen.h"
#include <iostream>
#include "ZoomList.h"
#include "Zoom.h"

Screen::Screen() :
    isWindowOpen(true),
    fractalCreator(windowWidth, windowHeight)
{
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
        fractalCreator.drawFractal(texture, renderer);

        while (SDL_PollEvent(&e))
        {
            if (e.key.type == SDL_QUIT)
            {
                isWindowOpen = false;
            }
        }
    }
}