//
// Created by ozgur on 31/01/2024.
//

#include <iostream>
#include "ZoomList.h"
#include "Zoom.h"

ZoomList::ZoomList(int _width, int _height) : width(_width), height(_height)
{}

void ZoomList::addZoom(const Zoom& zoom)
{
    zooms.push_back(zoom);

    xCenter += (zoom.xCord - width/2) * scale;
    yCenter += -(zoom.yCord - height/2) * scale;

    scale *= zoom.scale;

    std::cout << xCenter << " " << yCenter << " " << scale << std::endl;
}

std::pair<double, double> ZoomList::doZoom(int x, int y)
{
    double xFractal = (x - width/2) * scale + xCenter;
    double yFractal = (y - height/2) * scale + yCenter;

    return std::pair<double, double>(xFractal, yFractal);
}

void ZoomList::setZoom(double xC, double yC, double s)
{
    xCenter = xC;
    yCenter = yC;
    scale = s;
}
