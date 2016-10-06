#include "../drawing/bitmap.h"
#include "bitmapWriter.h"
#include "console.h"

bitmapWriter::bitmapWriter(uint width, uint height) :
    _width(width),
    _height(height),
    _data(new byte[width * height * 4])
{
}

void bitmapWriter::write(uint x, uint y, float r, float g, float b) const
{
    _data[(y * _width * 4) + (x * 4) + 0] = byte(255.9999f * b);
    _data[(y * _width * 4) + (x * 4) + 1] = byte(255.9999f * g);
    _data[(y * _width * 4) + (x * 4) + 2] = byte(255.9999f * r);
    _data[(y * _width * 4) + (x * 4) + 3] = 255;
}

void bitmapWriter::save(std::string fileName)
{
    bitmap bmp(_width, _height, _data);
    bmp.save(fileName);
}

bitmapWriter::~bitmapWriter()
{
    delete[] _data;
}


