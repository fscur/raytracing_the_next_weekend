#include "textWriter.h"
#include "ppmWriter.h"

ppmWriter::ppmWriter(uint width, uint height) :
    _width(width),
    _height(height),
    _data(new byte[width * height * 3])
{
}

void ppmWriter::write(uint x, uint y, float r, float g, float b) const
{
    _data[(y * _width * 3) + (x * 3) + 0] = byte(255.9999f * r);
    _data[(y * _width * 3) + (x * 3) + 1] = byte(255.9999f * g);
    _data[(y * _width * 3) + (x * 3) + 2] = byte(255.9999f * b);
}

void ppmWriter::save(std::string fileName)
{
    textWriter writer(fileName);
    auto header = "P3\n" + std::to_string(_width) + " " + std::to_string(_height) + "\n255\n";
    writer.writeLine(header);

    for (int y = _height - 1; y >= 0; --y)
    {
        for (int x = 0; x < _width; ++x)
        {
            auto r = _data[(y * _width * 3) + (x * 3) + 0];
            auto g = _data[(y * _width * 3) + (x * 3) + 1];
            auto b = _data[(y * _width * 3) + (x * 3) + 2];

            writer.writeLine(
                std::to_string(r) + " " +
                std::to_string(g) + " " +
                std::to_string(b));
        }
    }
}

ppmWriter::~ppmWriter()
{
    delete[] _data;
}


