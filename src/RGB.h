#ifndef FRACTAL_RGB_H
#define FRACTAL_RGB_H

struct RGB
{
    double red;
    double green;
    double blue;

    RGB(double red, double green, double blue);
};

RGB operator-(const RGB& first, const RGB& second);

#endif //FRACTAL_RGB_H
