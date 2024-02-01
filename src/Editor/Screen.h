//
// Created by ozgur on 28/01/2024.
//

#ifndef FRACTAL_SCREEN_H
#define FRACTAL_SCREEN_H

#include "SDL.h"
#include "../Fractal/FractalCreator.h"

class Screen
{
private:
    const int windowWidth = 800;
    const int windowHeight = 600;
    const char* windowName = "Fractal_Simulation";

    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};

    bool isWindowOpen;

    FractalCreator fractalCreator;
    int drawnFractalNumber;
public:
    Screen(int drawnFractalNumber);
    ~Screen();

    void init();
    void processEvent();
};

#endif //FRACTAL_SCREEN_H
