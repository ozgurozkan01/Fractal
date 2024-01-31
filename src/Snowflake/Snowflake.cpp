//
// Created by ozgur on 29/01/2024.
//

#include <iostream>
#include "Snowflake.h"

Snowflake::Snowflake()
{
    init();
}

Snowflake::~Snowflake()
{
    delete segment_1;
    delete segment_2;
    delete segment_3;

    for (auto seg : segments)
    {
        delete seg;
    }
}

void Snowflake::init()
{
    segment_1 = new Segment(vec2(200, 200), vec2(800, 200));
    segment_2 = new Segment(vec2(800, 200), vec2(500, 700));
    segment_3 = new Segment(vec2(500, 700), vec2(200, 200));

    segments.push_back(segment_1);
    segments.push_back(segment_2);
    segments.push_back(segment_3);

}

void Snowflake::drawSnowflake(SDL_Renderer* renderer)
{
    for (int i = 0; i < segments.size(); ++i)
    {
        segments[i]->show(renderer);
    }
}

void Snowflake::createNextGenerationSegments()
{
    std::vector<Segment*> nextGeneration;

    for (auto s : segments)
    {
        std::vector<Segment*> newChildren = s->generateSegment();
        addAllSegments(newChildren, nextGeneration);
    }

    segments = nextGeneration;
}

void Snowflake::addAllSegments(std::vector<Segment *>& childrenSegments, std::vector<Segment *>& segmentContainer)
{
    for (int i = 0; i < childrenSegments.size(); ++i)
    {
        segmentContainer.push_back(childrenSegments[i]);
    }
}
