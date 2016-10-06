#pragma once
#include <iostream>
#include <fstream>
#include <string>

class textWriter
{
public:
    textWriter(std::string fileName);

    void write(std::string text);
    void writeLine(std::string text);

    ~textWriter();

private:
    std::ofstream _file;
};