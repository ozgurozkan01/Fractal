//
// Created by ozgur on 28/01/2024.
//

#include "Screen.h"
#include <stdio.h>
Screen::Screen() :
    isWindowOpen(true)
{
    init();
}

Screen::~Screen()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Screen::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialise: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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
}

void Screen::update()
{
    SDL_Event e;

    while(isWindowOpen)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.key.type == SDL_QUIT)
            {
                isWindowOpen = false;
            }
        }
    }
}

void Screen::setPixels(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{

}
