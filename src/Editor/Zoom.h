//
// Created by ozgur on 31/01/2024.
//

#ifndef FRACTAL_ZOOM_H
#define FRACTAL_ZOOM_H


struct Zoom
{
    int xCord{0};
    int yCord{0};
    double scale{0.0};

    Zoom(int x, int y, double _scale) : xCord(x), yCord(y), scale(_scale)
    {}
};


#endif //FRACTAL_ZOOM_H
