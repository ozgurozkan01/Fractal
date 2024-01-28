//
// Created by ozgur on 28/01/2024.
//

#ifndef FRACTAL_SCREEN_H
#define FRACTAL_SCREEN_H

#include "SDL.h"

class Screen
{
private:
    static const int WINDOW_WIDTH = 600;
    static const int WINDOW_HEIGHT = 400;
    const char* WINDOW_NAME = "Fractal_Simulation";

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isWindowOpen;
public:

    Screen();
    ~Screen();

    void init();
    void update();
    void setPixels(int x, int y, uint8_t red, uint8_t green, uint8_t blue);

    inline static int getWindowWidth() { return WINDOW_WIDTH; }
    inline static int getWindowHeight() { return WINDOW_HEIGHT; }
};

#endif //FRACTAL_SCREEN_H
