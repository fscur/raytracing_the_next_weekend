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
    auto r0 = glm::clamp(255.9999f * r, 0.0f, 255.9999f);
    auto g0 = glm::clamp(255.9999f * g, 0.0f, 255.9999f);
    auto b0 = glm::clamp(255.9999f * b, 0.0f, 255.9999f);

    _data[(y * _width * 4) + (x * 4) + 0] = byte(b0);
    _data[(y * _width * 4) + (x * 4) + 1] = byte(g0);
    _data[(y * _width * 4) + (x * 4) + 2] = byte(r0);
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


