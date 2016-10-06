#pragma once

#include "../common/types.h"
#include "pixelWriter.h"

class bitmapWriter :
    public pixelWriter
{
public:
    bitmapWriter(uint width, uint height);
    virtual void write(uint x, uint y, float r, float g, float b) const override;
    virtual void save(std::string fileName);
    byte* getData() const { return _data; }
    ~bitmapWriter();

private:
    uint _width;
    uint _height;
    byte* _data;

};