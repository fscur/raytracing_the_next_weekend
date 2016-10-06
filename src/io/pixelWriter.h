#pragma once
#include "../common/types.h"

class pixelWriter
{
public:
    virtual void write(uint x, uint y, float r, float g, float b) const = 0;
    virtual void save(std::string fileName) = 0;
};
