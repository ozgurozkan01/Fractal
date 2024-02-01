#ifndef FRACTAL_FRACTALCREATOR_H
#define FRACTAL_FRACTALCREATOR_H

class Zoom;
class ZoomList;
class Mandelbrot;
class Snowflake;

class FractalCreator
{
private:
    int windowWidth;
    int windowHeight;
public:
    Mandelbrot* mandelbrot;
    Snowflake* snowflake;
    ZoomList* zoomlist;

    FractalCreator(int windowWidth, int windowHeigth);
    ~FractalCreator();

    void init();
    void showMandelbrotOnScreen(SDL_Texture* texture, SDL_Renderer* renderer);
    void drawFractal(SDL_Texture* texture, SDL_Renderer* renderer);
};


#endif //FRACTAL_FRACTALCREATOR_H
