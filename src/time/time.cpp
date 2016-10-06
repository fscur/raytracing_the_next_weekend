#include "time.h"

double time::totalSeconds = 0;
double time::deltaSeconds = 0;
stopwatch time::_stopwatch = stopwatch();

void time::start()
{
    _stopwatch.start();
    totalSeconds = _stopwatch.getElapsedMilliseconds();
    deltaSeconds = 0;
}

void time::update()
{
    auto totalSecondsLastFrame = totalSeconds;
    totalSeconds = _stopwatch.getElapsedSeconds();
    deltaSeconds = totalSeconds - totalSecondsLastFrame;
}
