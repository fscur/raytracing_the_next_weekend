#pragma once

#include "../common/types.h"
#include "pixelWriter.h"

class ppmWriter : 
    public pixelWriter
{
public:
    ppmWriter(uint width, uint height);
    virtual void write(uint x, uint y, float r, float g, float b) const override;
    virtual void save(std::string fileName);
    ~ppmWriter();

private:
    uint _width;
    uint _height;
    byte* _data;

};