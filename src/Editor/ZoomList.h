//
// Created by ozgur on 31/01/2024.
//

#ifndef FRACTAL_ZOOMLIST_H
#define FRACTAL_ZOOMLIST_H

#include <vector>
#include <utility>

class Zoom;

class ZoomList
{
private:
    double xCenter{0.0};
    double yCenter{0.0};
    double scale{1.0};

    int width{0};
    int height{0};
    std::vector<Zoom> zooms;
    std::vector<std::pair<double,double>> m_zoom_positions;
    std::vector<double> m_zoom_scale;

public:
    ZoomList(int _width, int _height);
    void addZoom(const Zoom& zoom);
    std::pair<double, double> doZoom(int x, int y);
    void setZoom(double xC, double yC, double s);
};
#endif //FRACTAL_ZOOMLIST_H