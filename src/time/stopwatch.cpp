#include "stopwatch.h"
#include <iostream>

using namespace std::chrono;

stopwatch::stopwatch() :
    _initial(std::chrono::nanoseconds()),
    _stop(std::chrono::nanoseconds()),
    _isRunning(false)
{
}

void stopwatch::start()
{
    if (!_isRunning)
    {
        _isRunning = true;
        auto now = high_resolution_clock::now();
        _initial = _stop = duration_cast<nanoseconds>(now.time_since_epoch());
    }
}

void stopwatch::stop()
{
    if (_isRunning)
    {
        auto now = high_resolution_clock::now();
        _stop = duration_cast<nanoseconds>(now.time_since_epoch());
        _isRunning = false;
    }
}

void stopwatch::resume()
{
    if (!_isRunning)
    {
        auto now = high_resolution_clock::now().time_since_epoch();
        _initial += now - _stop;
        _isRunning = true;
    }
}

double stopwatch::getElapsedSeconds()
{
    auto now = high_resolution_clock::now().time_since_epoch();
    return duration_cast<duration<double>>(now - _initial).count();
}

double stopwatch::getElapsedMilliseconds()
{
    auto now = high_resolution_clock::now().time_since_epoch();
    return duration_cast<duration<double>>(now - _initial).count() * 1000;
}

double stopwatch::measure(const std::function<void(void)> &function)
{
    auto watch = stopwatch();
    watch.start();
    function();
    watch.stop();

    return watch.getElapsedSeconds();
}

double stopwatch::measure(const std::function<void(void)> &function, const std::string &functionName)
{
    auto msg = functionName + " took: ";
    auto elapsedSeconds = stopwatch::measure(function);
    std::cout << msg + std::to_string(elapsedSeconds) << "s" << std::endl;

    return elapsedSeconds;
}

double stopwatch::measureAverage(const std::function<void(void)> &function, const std::string &functionName, int samples)
{
    double average = stopwatch::measureAverage(function, samples);

    auto msg = "average of " + std::to_string(samples) + " samples for " + functionName + " took: ";
    std::cout << msg << std::to_string(average) << "s" << std::endl;

    return average;
}

double stopwatch::measureAverage(const std::function<void(void)> &function, int samples)
{
    double average = 0;
    auto watch = stopwatch();

    for (auto i = 0; i < samples; i++)
    {
        watch.start();
        function();
        watch.stop();
        average += watch.getElapsedSeconds();
    }

    return average / samples;
}