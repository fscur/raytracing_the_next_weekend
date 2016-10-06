#pragma once
#include <cstdlib>

class random
{
public:
    static float next()
    {
        return float(rand())/float(RAND_MAX);
    }
};