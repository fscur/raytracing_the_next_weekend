#pragma once
#include <string>
#include <iostream>

class console
{
public:
    static void write(std::string message)
    {
        std::cout << message;
    }

    static void writeLine(std::string message)
    {
        std::cout << message << std::endl;
    }
};
