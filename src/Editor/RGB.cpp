//
// Created by ozgur on 01/02/2024.
//

#include "RGB.h"

RGB::RGB(double red, double green, double blue) :
    red(red),
    green(green),
    blue(blue)
{}

RGB operator-(const RGB &first, const RGB &second)
{
    return RGB(first.red - second.red, first.green - second.green, first.blue - second.blue);
}
