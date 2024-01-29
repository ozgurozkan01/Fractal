//
// Created by ozgur on 29/01/2024.
//

#include <iostream>
#include "Segment.h"


Segment::Segment() : start(vec2()), end(vec2())
{}

Segment::Segment(vec2 _start, vec2 _end)
{
    start = _start;
    end = _end;
}

std::vector<Segment*> Segment::generateSegment() const
{
    std::vector<Segment*> children = {nullptr, nullptr, nullptr, nullptr};

    vec2 v = vec2::subtract(end, start);
    v.div(3);
    // Segment 0
    vec2 b1 = vec2::add(start, v);
    children[0] = new Segment(start, b1);

    // Segment 3
    vec2 a1 = vec2::subtract(end, v);
    children[3] = new Segment(a1, end);

    v.rotate(-(M_PI/3));
    std::cout << "Vector Length : " << v.getLength() << std::endl;
    vec2 c = vec2::add(b1, v);
    children[1] = new Segment(b1, c);
    children[2] = new Segment(c, a1);

    return children;
}

void Segment::show(SDL_Renderer* renderer) const
{
    if (renderer)
    {
        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }
}