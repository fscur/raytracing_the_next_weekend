#pragma once
#include "stopwatch.h"

class time
{
private:
    static stopwatch _stopwatch;

public:
    static double totalSeconds;
    static double deltaSeconds;

public:
    static void start();
    static void update();
};