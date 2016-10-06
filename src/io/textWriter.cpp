#include "textWriter.h"

textWriter::textWriter(std::string fileName)
{
    _file.open (fileName);
}

void textWriter::write(std::string text)
{
    _file << text;
}

void textWriter::writeLine(std::string text)
{
    _file << text << std::endl;
}

textWriter::~textWriter()
{
    _file.close();
}