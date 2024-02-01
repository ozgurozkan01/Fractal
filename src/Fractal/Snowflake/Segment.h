//
// Created by ozgur on 29/01/2024.
//

#ifndef FRACTAL_SEGMENT_H
#define FRACTAL_SEGMENT_H

#include <vector>
#include "SDL.h"
#include <cmath>

struct vec2
{
    int x;
    int y;

    vec2(int _x = 0, int _y = 0)
    {
        x = _x;
        y = _y;
    }

    static vec2 subtract (vec2 v1, vec2 v2)
    {
        vec2 result;
        result.x = v1.x - v2.x;
        result.y = v1.y - v2.y;

        return result;
    }

    void div(int divider)
    {
        x /= divider;
        y /= divider;
    }

    static vec2 add (vec2 v1, vec2 v2)
    {
        vec2 result;
        result.x = v1.x + v2.x;
        result.y = v1.y + v2.y;

        return result;
    }

    void rotate (float radian)
    {
        int newX = (int)((x * cos(radian) - y * sin(radian)));
        int newY = (int)((x * sin(radian) + y * cos(radian)));

        x = newX;
        y = newY;}

    double getLength()
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
};

class Segment{

public:
    vec2 start;
    vec2 end;

    Segment();
    Segment(vec2 _start, vec2 _end);


    std::vector<Segment*> generateSegment() const;
    void show(SDL_Renderer* renderer) const;
};


#endif //FRACTAL_SEGMENT_H
