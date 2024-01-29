//
// Created by ozgur on 29/01/2024.
//

#ifndef FRACTAL_SNOWFLAKE_H
#define FRACTAL_SNOWFLAKE_H

#include <vector>
#include "Segment.h"

class Snowflake{

private:
    std::vector<Segment*> segments;
    std::vector<Segment*>  children;

    Segment* segment_1;
    Segment* segment_2;
    Segment* segment_3;

public:
    Snowflake();
    ~Snowflake();

    void init();
    void drawSnowflake(SDL_Renderer* renderer);
    void createNextGenerationSegments();
    void addAllSegments(std::vector<Segment*>& childrenSegments, std::vector<Segment*>& segmentContainer);
};


#endif //FRACTAL_SNOWFLAKE_H
