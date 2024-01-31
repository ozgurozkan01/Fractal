#include "Screen.h"
#include <iostream>

Screen::Screen() :
    isWindowOpen(true),
    windowPixels(new uint32_t[windowHeight * windowWidth]{0}),
    histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
    pixelIterations(new int[windowHeight * windowWidth]{0}),
    mandelbrot(new Mandelbrot()),
    snowflake(new Snowflake())
{
    init();
}

Screen::~Screen()
{
    delete [] windowPixels;
    delete [] histogram;
    delete [] pixelIterations;
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

        drawFractal(0);

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

void Screen::drawFractal(int n)
{
    switch (n)
    {
        /* Mandelbrot */
        case 0:
            drawMandelbrot();
            break;

        /* Snowflake */
        case 1:
            drawSnowflake();
        default:
            break;
    }
}

void Screen::drawMandelbrot()
{
    SDL_UpdateTexture(texture, nullptr, windowPixels, windowWidth * sizeof(Uint32));
    SDL_RenderClear(renderer); // Clear renderer which render the data its stored.
    SDL_RenderCopy(renderer, texture, nullptr, nullptr); // Fill the renderer via texture
    SDL_RenderPresent(renderer);

    // Get the iteration of each pixel and  stored in the array
    for (int row = 0; row < windowHeight; ++row)
    {
        for (int column = 0; column < windowWidth; ++column)
        {

            int slideToRight = 250;
            double xFractal = (column - windowWidth / 2 -slideToRight) * (2.0 / windowHeight);
            double yFractal = (row - windowHeight / 2) * (2.0 / windowHeight);

            // get the iteration of the particular pixel
            int iteration = mandelbrot->getIterations(xFractal, yFractal);
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

    int total = 0;
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
    {
        total += histogram[i];
    }
    
    for (int row = 0; row < windowHeight; ++row)
    {
        for (int column = 0; column < windowWidth; ++column)
        {
            // Set RGB colors
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            // Get iteration of particular pixel by using its index
            int iteration = pixelIterations[column * windowHeight + row];
            // Ignore the pixels whose iterations equals to the max iteration
            if (iteration != Mandelbrot::MAX_ITERATIONS)
            {
                double hue = 0.0;
                for (int i = 0; i <= iteration; ++i)
                {
                    // Find all pixels color hue separately
                    hue += ((double)histogram[i]) / total;
                }

                green = pow(255, hue);
            }

            setPixel(column, row, red, green, blue);
        }
    }
}

void Screen::drawSnowflake()
{
    if (renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        snowflake->drawSnowflake(renderer);
        SDL_RenderPresent( renderer );
    }
}
